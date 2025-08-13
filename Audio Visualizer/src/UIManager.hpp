
#pragma once
#include <SFML/Graphics.hpp>
#include "AudioManager.hpp"
#include <vector>
#include <functional>

struct Button {
    sf::RectangleShape shape;
    sf::Text text;
};

class UIManager {
public:
    UIManager(AudioManager& audio, sf::Font& font);
    void handleClick(sf::Vector2f mousePos);
    void draw(sf::RenderWindow& window);
    void setOnEffectsMenuRequested(std::function<void()> cb) { onEffectsMenuRequested = cb; }

private:
    void setupButtons();
    void setupRewindButtons();
    void toggleRecording();
    bool effectsMenuVisible = false;
    AudioManager& audioManager;
    sf::Font& font;
    std::vector<Button> buttons;
    bool isRecording;
    std::function<void()> onEffectsMenuRequested;
    bool rewindMenuVisible = false;
    std::vector<Button> rewindButtons;
};
