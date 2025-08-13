#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include "AudioManager.hpp"

class Visualizer {
public:
    Visualizer(AudioManager& audio, sf::RenderWindow& win);
    void draw();

private:
    AudioManager& audioManager;
    sf::RenderWindow& window;
    std::vector<sf::RectangleShape> bars;
    std::vector<float> previousHeights;  // for smoothing
    sf::RectangleShape timeScaleBar;
    sf::RectangleShape progressMarker;
};

