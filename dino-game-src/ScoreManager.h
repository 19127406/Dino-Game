#pragma once

#include "core.h"

class ScoreManager {
private:
    int _score;       // Current score
    int _highScore;   // High score

    sf::Text _scoreText;      // Displays current score
    sf::Text _highScoreText;  // Displays high score
    sf::Font _font;           // Font for text

public:
    ScoreManager() : _score(0), _highScore(0) {
        // Load font
        if (!_font.loadFromFile("../assets/fonts/press_start_2p.ttf"))
        {
            std::cerr << "Error loading font" << std::endl;
        }

        // Configure score text
        _scoreText.setFont(_font);
        _scoreText.setCharacterSize(16);
        _scoreText.setFillColor(sf::Color::Black);
        _scoreText.setPosition(10.f, 40.f);  // Top-left corner
        updateScoreText();

        // Configure high score text
        _highScoreText.setFont(_font);
        _highScoreText.setCharacterSize(14);
        _highScoreText.setFillColor(sf::Color::Black);
        _highScoreText.setPosition(10.f, 10.f);  // Below current score
        _highScoreText.setStyle(sf::Text::Bold);
        updateHighScoreText();
    }

    // Add points to the current score
    void addScore(int points) {
        _score += points;
        updateScoreText();
    }

    // Reset the score but retain the high score
    void reset() {
        updateHighScore();  // Update high score before resetting
        _score = 0;
        updateScoreText();
    }

    // Check and update the high score
    void updateHighScore() {
        if (_score > _highScore) {
            _highScore = _score;
            updateHighScoreText();
        }
    }

    // Draw both score and high score on the window
    void draw(sf::RenderWindow& window) {
        window.draw(_highScoreText);
        window.draw(_scoreText);
    }

private:
    // Update the text for the current score
    void updateScoreText() {
        _scoreText.setString("Score " + std::to_string(_score));
    }

    // Update the text for the high score
    void updateHighScoreText() {
        _highScoreText.setString("High Score " + std::to_string(_highScore));
    }
};
