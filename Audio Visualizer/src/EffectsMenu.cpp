#include "EffectsMenu.hpp"

EffectsMenu::EffectsMenu(AudioManager& audio, sf::Font& font)
    : font(font), audioManager(audio) {
    std::vector<std::string> names = { "Pitch", "Volume"};

    for (int i = 0; i < static_cast<int>(names.size()); ++i) {

        Slider s;
        s.track.setSize({ 200, 5 });
        s.track.setFillColor(sf::Color::White);
        s.track.setPosition(200, 100 + i * 60);

        s.knob.setSize({ 10, 20 });
        s.knob.setFillColor(sf::Color::Red);
        s.knob.setPosition(200 + 100, 95 + i * 60);

        s.value = 1.f;
        s.label = names[i];

        // NEW: Setup label text
        s.text.setFont(font);
        s.text.setCharacterSize(14);
        s.text.setFillColor(sf::Color::White);
        s.text.setString(s.label);
        s.text.setPosition(s.track.getPosition() - sf::Vector2f(60, 10));  // to the left of track
        
        s.valueText.setFont(font);
	s.valueText.setCharacterSize(14);
	s.valueText.setFillColor(sf::Color::White);
	s.valueText.setPosition(s.track.getPosition() + sf::Vector2f(210, -10));  // to the right of track
	s.valueText.setString("1.00");  // initial value shown


        sliders.push_back(s);
    }


    title.setFont(font);
    title.setCharacterSize(20);
    title.setString("Sound Effects");
    title.setPosition(200, 50);
}

void EffectsMenu::handleEvent(const sf::Event& e, sf::Vector2f mousePos) {
    if (!visible) return;

    if (e.type == sf::Event::MouseButtonPressed) {
        for (auto& s : sliders) {
            if (s.track.getGlobalBounds().contains(mousePos)) {
                float rel = (mousePos.x - s.track.getPosition().x) / s.track.getSize().x;
                s.value = rel;
                char buffer[16];
		if (s.label == "Volume")
		    snprintf(buffer, sizeof(buffer), "%.0f", s.value * 100);
		else
		    snprintf(buffer, sizeof(buffer), "%.2f", s.value * 2);

		s.valueText.setString(buffer);

                s.knob.setPosition(s.track.getPosition().x + rel * 200 - 5, s.knob.getPosition().y);
                applyEffects();
            }
        }
    }
}

void EffectsMenu::applyEffects() {
    float pitch = sliders[0].value * 2;
    float vol = sliders[1].value * 100;

    audioManager.setEffects(pitch, vol);
}

void EffectsMenu::draw(sf::RenderWindow& window) {
    if (!visible) return;

    window.draw(title);
    for (auto& s : sliders) {
        window.draw(s.track);
        window.draw(s.knob);
        window.draw(s.text);
        window.draw(s.valueText);  // NEW
    }

}

