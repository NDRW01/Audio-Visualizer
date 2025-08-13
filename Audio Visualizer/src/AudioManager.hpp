#pragma once
#include <SFML/Audio.hpp>
#include <string>

class AudioManager {
public:
    bool load(const std::string& filepath);
    void loadAudio(); // new
    void play();
    void pause();
    void togglePlayPause();
    void rewind(); // new
    void recordStart(); // already implemented
    void recordStop();  // already implemented
    void setEffects(float pitch, float volume); // new
    void rewindBy(float seconds);
    void rewindToStart();
    void forwardBy(float seconds);
    void rewindToEnd();
    sf::Time getPlayingOffset() const;
    sf::SoundSource::Status getStatus() const;


    const sf::SoundBuffer& getBuffer() const { return buffer; }
    const sf::Sound& getSound() const { return sound; }
    bool isPausedManually() const { return isManuallyPaused; }

private:
    sf::SoundBuffer buffer;
    sf::Sound sound;
    sf::SoundBuffer recordedBuffer;
    bool recording = false;
    sf::Time startOffset;
    sf::Time recordStartOffset;
    bool isManuallyPaused = false;
};

