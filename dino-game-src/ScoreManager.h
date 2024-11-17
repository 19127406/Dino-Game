#pragma once

#include "core.h"

class ScoreManager {
private:
    int score;
    sf::Text scoreText;
    sf::Font font;

public:
    ScoreManager() : score(0) {
        // Load font
        if (!font.loadFromFile("../assets/fonts/press_start_2p.ttf")) {  // Replace with your font path
            std::cerr << "Error loading font" << std::endl;
        }

        // Configure score text
        scoreText.setFont(font);
        scoreText.setCharacterSize(24);
        scoreText.setFillColor(sf::Color::Black);
        scoreText.setPosition(10.f, 10.f);  // Top-left corner
        updateScoreText();
    }

    void addScore(int points) {
        score += points;
        updateScoreText();
    }

    void reset() {
        score = 0;
        updateScoreText();
    }

    void draw(sf::RenderWindow& window) {
        window.draw(scoreText);
    }

private:
    void updateScoreText() {
        scoreText.setString("Score: " + std::to_string(score));
    }
};