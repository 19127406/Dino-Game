#pragma once

#include "core.h"

class ScoreManager {
private:
    int _score;
    int _highScore;
    sf::Text _scoreText;
    sf::Font _font;

public:
    ScoreManager() : _score(0) {
        // Load font
        if (!_font.loadFromFile("../assets/fonts/press_start_2p.ttf")) {  // Replace with your font path
            std::cerr << "Error loading font" << std::endl;
        }

        // Configure score text
        _scoreText.setFont(_font);
        _scoreText.setCharacterSize(24);
        _scoreText.setFillColor(sf::Color::Black);
        _scoreText.setPosition(10.f, 10.f);  // Top-left corner
        updateScoreText();
    }

    void addScore(int points) {
        _score += points;
        updateScoreText();
    }

    void reset() {
        _score = 0;
        updateScoreText();
    }

    void draw(sf::RenderWindow& window) {
        window.draw(_scoreText);
    }

private:
    void updateScoreText() {
        _scoreText.setString("Score: " + std::to_string(_score));
    }
};