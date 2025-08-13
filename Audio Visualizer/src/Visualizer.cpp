#include "Visualizer.hpp"
extern "C" {
    #include "kiss_fft.h"
}
#include "SimpleFFT.hpp"


Visualizer::Visualizer(AudioManager& audio, sf::RenderWindow& win)
    : audioManager(audio), window(win) {
    bars.resize(64, sf::RectangleShape(sf::Vector2f(10, 0)));
    for (size_t i = 0; i < bars.size(); ++i) {
        bars[i].setPosition(200 + i * 12, 400);
        bars[i].setFillColor(sf::Color::Green);
    }
    timeScaleBar.setSize({ static_cast<float>(bars.size()) * 12, 2 });  // Same width as bars
    timeScaleBar.setFillColor(sf::Color::White);
    timeScaleBar.setPosition(200, 430);  // Below bars (400) + space

    progressMarker.setSize({ 2, 10 });  // Thin vertical line
    progressMarker.setFillColor(sf::Color::Red);

}

void Visualizer::draw() {
    const sf::SoundBuffer& buf = audioManager.getBuffer();
    const sf::Sound& sound = audioManager.getSound();
    sf::Time offset = sound.getPlayingOffset();
    const sf::Int16* samples = buf.getSamples();
    size_t sampleRate = buf.getSampleRate() * buf.getChannelCount();
    size_t offsetSample = static_cast<size_t>(offset.asSeconds() * sampleRate);

    std::vector<float> sampleWindow(128);
    for (size_t i = 0; i < 128 && (offsetSample + i) < buf.getSampleCount(); ++i)
        sampleWindow[i] = static_cast<float>(samples[offsetSample + i]);

    std::vector<float> magnitudes;
    SimpleFFT::compute(sampleWindow, magnitudes, 128);

    if (magnitudes.empty()) return;

    // Find max magnitude for normalization (avoid division by zero)
    float maxMagnitude = *std::max_element(magnitudes.begin(), magnitudes.end());
    if (maxMagnitude == 0) maxMagnitude = 1.f;

    float maxBarHeight = 150.f;  // max height in pixels for bars

    for (size_t i = 0; i < bars.size(); ++i) {
        float mag = (i < magnitudes.size()) ? magnitudes[i] : 0.f;
        float normalizedHeight = (mag / maxMagnitude) * maxBarHeight;
        bars[i].setSize(sf::Vector2f(10, -normalizedHeight));  // negative for upward growth
        window.draw(bars[i]);
    }
    // Draw time scale
    window.draw(timeScaleBar);

    // Progress marker
    sf::Time current = audioManager.getPlayingOffset();
    sf::Time total = audioManager.getBuffer().getDuration();

    float progressRatio = current.asSeconds() / total.asSeconds();
    float progressX = timeScaleBar.getPosition().x + progressRatio * timeScaleBar.getSize().x;

    progressMarker.setPosition(progressX, timeScaleBar.getPosition().y - 4);
    window.draw(progressMarker);

}
