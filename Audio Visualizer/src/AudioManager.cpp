#include "AudioManager.hpp"
#include "tinyfiledialogs.h"
#include <iostream>

bool AudioManager::load(const std::string& filepath) {
    if (!buffer.loadFromFile(filepath)) {
        std::cerr << "Failed to load audio file: " << filepath << "\n";
        return false;
    }
    sound.setBuffer(buffer);
    return true;
}

void AudioManager::play() {
    sound.play();
    startOffset = sound.getPlayingOffset();
}

void AudioManager::pause() {
    sound.pause();
}

void AudioManager::togglePlayPause() {
    if (sound.getStatus() == sf::Sound::Playing) {
        sound.pause();
        isManuallyPaused = true;
    } else {
        sound.play();
        isManuallyPaused = false;
    }
}

void AudioManager::recordStart() {
    recording = true;
    recordStartOffset = sound.getPlayingOffset();
}

void AudioManager::recordStop() {
    if (!recording) return;
    recording = false;
    sf::Time endOffset = sound.getPlayingOffset();
    sf::Uint64 startSample = static_cast<sf::Uint64>(recordStartOffset.asSeconds() * buffer.getSampleRate() * buffer.getChannelCount());
    sf::Uint64 endSample = static_cast<sf::Uint64>(endOffset.asSeconds() * buffer.getSampleRate() * buffer.getChannelCount());
    recordedBuffer.loadFromSamples(buffer.getSamples() + startSample, endSample - startSample, buffer.getChannelCount(), buffer.getSampleRate());
    recordedBuffer.saveToFile("recorded_output.wav");
}

void AudioManager::rewindBy(float seconds) {
    sf::Time current = sound.getPlayingOffset();
    sf::Time newTime = current - sf::seconds(seconds);
    if (newTime < sf::Time::Zero) newTime = sf::Time::Zero;
    sound.setPlayingOffset(newTime);
}

void AudioManager::rewindToStart() {
    sound.setPlayingOffset(sf::Time::Zero);
}

void AudioManager::forwardBy(float seconds) {
    sf::Time current = sound.getPlayingOffset();
    sf::Time newTime = current + sf::seconds(seconds);
    if (newTime > buffer.getDuration()) newTime = buffer.getDuration();
    sound.setPlayingOffset(newTime);
}

void AudioManager::rewindToEnd() {
    sound.setPlayingOffset(buffer.getDuration() - sf::seconds(1.0f));
    sound.pause();
}


void AudioManager::loadAudio() {
    const char* filePath = tinyfd_openFileDialog(
        "Load Audio File", "", 0, nullptr, nullptr, 0);

    if (!filePath || std::string(filePath).empty()) {
        std::cerr << "No file selected or dialog canceled.\n";
        return;
    }

    // 💥 SAFETY STEP: Stop sound before loading new buffer
    sound.stop();

    // Optional: detach buffer (good practice)
    sound.setBuffer(sf::SoundBuffer());

    // Now load new buffer
    if (!buffer.loadFromFile(filePath)) {
        std::cerr << "Failed to load audio from: " << filePath << "\n";
        return;
    }

    sound.setBuffer(buffer);
    sound.setPlayingOffset(sf::seconds(0));  // Reset to beginning
    std::cout << "Audio loaded successfully from: " << filePath << "\n";
}



void AudioManager::setEffects(float pitch, float volume) {
    sound.setPitch(pitch);
    sound.setVolume(volume);
}

sf::Time AudioManager::getPlayingOffset() const {
    return sound.getPlayingOffset();
}

sf::SoundSource::Status AudioManager::getStatus() const {
    return sound.getStatus();
}


