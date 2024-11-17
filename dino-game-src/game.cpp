#include "game.h"

Game::Game() {
	// set game text
    _overlayText.setText("DINO GAME");
    _overlayText.setTextSize(32);
    _overlayText.setTextPosition(
        (static_cast<float>(window_width) / 2) - (_overlayText.getTextBoundW() / 2),
		_restartButton.getPositionY() - 50.0f
    );

    _instructionText.setText("SPACE to play");
    _instructionText.setTextSize(16);
    _instructionText.setTextPosition(
        (static_cast<float>(window_width) / 2) - (_instructionText.getTextBoundW() / 2),
        static_cast<float>(window_height / 2)
    );
}

Game::~Game() {}

void Game::update(sf::Time& deltaTime) {
    if (_inGame) {
        if (!_dino.isDead()) {
            // Update game objects and speed
            _gameSpeedDino += _speedIncrementDino * deltaTime.asSeconds();

            _dino.update(deltaTime, _gameSpeedDino);
            _ground.update();
            _obstacles.update(deltaTime, _gameSpeedObs);

            // Increment the score periodically
            if (_scoreClock.getElapsedTime().asSeconds() > 0.5f) {  // Increase score every 0.5 seconds
                _scoreManager.addScore(10);  // Add 10 points
                _scoreClock.restart();
            }

            // Check for collision
            if (_obstacles.checkCollision(_dino)) {
                _ground.stopMusic();
                _dino.setDead(true);
            }
        }
        else {
            // Display "Game Over" and reset game
            _overlayText.setText("GAME OVER");
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
                _dino.setDead(false);

                _dino.reset();
                _ground.reset();
                _obstacles.reset();
                _scoreManager.reset();  // Reset the score
            }
        }
    }
    else {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
            _inGame = true;
    }

    // Clouds continue moving
    _clouds.update(deltaTime);
}


void Game::draw(sf::RenderWindow& window) {
    if (_inGame) {
        // Draw game objects
        window.draw(_dino.dino);
        window.draw(_ground.groundSprite);
        _obstacles.draw(window);
        _clouds.draw(window);

        // Draw the score
        _scoreManager.draw(window);

        if (_dino.isDead()) {
            _overlayText.draw(window);
            _restartButton.draw(window);
        }
    }
    else {
        _overlayText.draw(window);
        _instructionText.draw(window);
    }
}
