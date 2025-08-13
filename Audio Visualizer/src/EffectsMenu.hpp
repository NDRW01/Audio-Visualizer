#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include "AudioManager.hpp"

struct Slider {
    sf::RectangleShape track;
    sf::RectangleShape knob;
    float value = 1.f;
    std::string label;
    sf::Text text;  // Label to show name like "Pitch", "Volume", "Speed"
    sf::Text valueText;  // Shows numeric value
};

class EffectsMenu {
public:
    EffectsMenu(AudioManager& audio, sf::Font& font);
    void handleEvent(const sf::Event& e, sf::Vector2f mousePos);
    void draw(sf::RenderWindow& window);
    void setVisible(bool v) { visible = v; }
    bool isVisible() const { return visible; }

private:
    void applyEffects();
    std::vector<Slider> sliders;
    sf::Text title;
    sf::Font& font;
    AudioManager& audioManager;
    bool visible;
    sf::Text pitchLabel;
    sf::Text volumeLabel;

};
