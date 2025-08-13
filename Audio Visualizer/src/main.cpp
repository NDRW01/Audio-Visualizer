#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include "AudioManager.hpp"
#include "UIManager.hpp"
#include "EffectsMenu.hpp"
#include "Visualizer.hpp"  // <-- Add this
#include <unistd.h>
#include <limits.h>

int main() {
    sf::RenderWindow window(sf::VideoMode(1000, 700), "Audio Visualizer");
    window.setFramerateLimit(60);

    sf::Font font;
    if (!font.loadFromFile("assets/font.ttf")) {
        std::cerr << "Failed to load font\n";
        return 1;
    }

    AudioManager audioManager;
    if (!audioManager.load("assets/audio.wav")) {  // <-- Make sure this line exists
        std::cerr << "Failed to load audio\n";
        return 1;
    }

    UIManager ui(audioManager, font);
    EffectsMenu effectsMenu(audioManager, font);
    Visualizer visualizer(audioManager, window);  // <-- Create Visualizer

    audioManager.play();  // <-- Don't forget to start playing audio!

    ui.setOnEffectsMenuRequested([&]() {
        effectsMenu.setVisible(!effectsMenu.isVisible());
    });

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();

            if (event.type == sf::Event::MouseButtonPressed &&
	        event.mouseButton.button == sf::Mouse::Left) {
	        sf::Vector2f mousePos = window.mapPixelToCoords(
		sf::Vector2i(event.mouseButton.x, event.mouseButton.y));
	        ui.handleClick(mousePos);
	        effectsMenu.handleEvent(event, mousePos);
	    }

        }

        window.clear();
        ui.draw(window);
        effectsMenu.draw(window);
        visualizer.draw();  // <-- Draw the visualizer
        window.display();
    }

    return 0;
}

