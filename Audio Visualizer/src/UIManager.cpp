#include "UIManager.hpp"
#include <iostream>

UIManager::UIManager(AudioManager& audio, sf::Font& font)
    : audioManager(audio), font(font), isRecording(false), rewindMenuVisible(false) {
    setupButtons();
    setupRewindButtons();
}

void UIManager::setupButtons() {
    const float startX = 20.f;
    const float startY = 20.f;
    const float spacing = 60.f;
    const sf::Vector2f btnSize(140.f, 40.f);

    std::vector<std::string> labels = { "Play/Pause", "Rewind/Forward", "Load Audio", "Record", "Effects" };

    for (size_t i = 0; i < labels.size(); ++i) {
        Button btn;
        btn.shape.setSize(btnSize);
        btn.shape.setFillColor(sf::Color(80, 80, 80));
        btn.shape.setPosition(startX, startY + i * spacing);

        btn.text.setFont(font);
        btn.text.setCharacterSize(16);
        btn.text.setString(labels[i]);
        btn.text.setFillColor(sf::Color::White);
        btn.text.setPosition(btn.shape.getPosition() + sf::Vector2f(10.f, 10.f));

        buttons.push_back(btn);
    }
}

void UIManager::setupRewindButtons() {
    std::vector<std::string> labels = {
    "Start", "-60s", "-15s", "-5s", "-1s", "+1s", "+5s", "+15s", "+60s", "End"
};


    float spacing = 10.f;
    float buttonWidth = 60.f;
    float buttonHeight = 30.f;
    float totalWidth = labels.size() * buttonWidth + (labels.size() - 1) * spacing;

    float startX = 800 / 2.f - totalWidth / 2.f; // assuming 800px width; adjust dynamically if needed
    float y = 600 - 50.f; // assuming 600px height; adjust if needed

    for (size_t i = 0; i < labels.size(); ++i) {
        Button btn;
        btn.shape.setSize(sf::Vector2f(buttonWidth, buttonHeight));
        btn.shape.setFillColor(sf::Color(50, 50, 50));
        btn.shape.setPosition(startX + i * (buttonWidth + spacing), y);

        btn.text.setFont(font);
        btn.text.setCharacterSize(16);
        btn.text.setString(labels[i]);
        btn.text.setFillColor(sf::Color::White);
        btn.text.setPosition(btn.shape.getPosition() + sf::Vector2f(10.f, 5.f));

        rewindButtons.push_back(btn);
    }
}

void UIManager::handleClick(sf::Vector2f mousePos) {
    for (size_t i = 0; i < buttons.size(); ++i) {
        if (buttons[i].shape.getGlobalBounds().contains(mousePos)) {
            switch (i) {
                case 0:
                    audioManager.togglePlayPause();
                    break;
                case 1:
                    rewindMenuVisible = !rewindMenuVisible;
                    break;
                case 2:
                    audioManager.loadAudio();
                    break;
                case 3:
                    toggleRecording();
                    break;
                case 4:
                    effectsMenuVisible = !effectsMenuVisible;
                    if (effectsMenuVisible && onEffectsMenuRequested)
                        onEffectsMenuRequested();
                    break;
            }
        }
    }

    if (rewindMenuVisible) {
        for (size_t i = 0; i < rewindButtons.size(); ++i) {
            if (rewindButtons[i].shape.getGlobalBounds().contains(mousePos)) {
                switch (i) {
                    case 0: audioManager.rewindToStart(); break;
                    case 1: audioManager.rewindBy(60.f); break;
                    case 2: audioManager.rewindBy(15.f); break;
                    case 3: audioManager.rewindBy(5.f); break;
                    case 4: audioManager.rewindBy(1.f); break;
                    case 5: audioManager.forwardBy(1.f); break;
                    case 6: audioManager.forwardBy(5.f); break;
                    case 7: audioManager.forwardBy(15.f); break;
                    case 8: audioManager.forwardBy(60.f); break;
                    case 9: audioManager.rewindToEnd(); break;
                }
                rewindMenuVisible = false;
            }
        }
    }

}

void UIManager::toggleRecording() {
    isRecording = !isRecording;
    if (isRecording)
        audioManager.recordStart();
    else
        audioManager.recordStop();
}

void UIManager::draw(sf::RenderWindow& window) {
    for (auto& btn : buttons) {
        window.draw(btn.shape);
        window.draw(btn.text);
    }

    if (rewindMenuVisible) {
        for (auto& btn : rewindButtons) {
            window.draw(btn.shape);
            window.draw(btn.text);
        }
    }
}

