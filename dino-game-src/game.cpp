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
            // Update game speed gradually over time
            _gameSpeedDino += _speedIncrementDino * deltaTime.asSeconds();
            _gameSpeedObs += _speedIncrementObs * deltaTime.asSeconds();

            _dino.update(deltaTime, _gameSpeedDino);
            _ground.update(_gameSpeedObs);

            // Update obstacles and score for avoided ones
            int avoidedObstacles = _obstacles.update(deltaTime, _gameSpeedObs);
            _scoreManager.addScore(avoidedObstacles * 100);

            // Check if Dino collides with an obstacle
            if (_obstacles.checkCollision(_dino)) {
                _ground.stopMusic();
                _dino.setDead(true);
                _scoreManager.updateHighScore();  // Update high score on collision
            }
        }
        else {
            // Handle game over state
            _overlayText.setText("GAME OVER");
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
                _dino.setDead(false);

                _dino.reset();
                _ground.reset();
                _obstacles.reset();
                _scoreManager.reset();  // Reset current score
            }
        }
    }
    else {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
            _inGame = true;
        }
    }

    _clouds.update(deltaTime);  // Clouds keep moving
}

void Game::draw(sf::RenderWindow& window) {
    if (_inGame) {
        // Draw game objects
        window.draw(_dino.dino);
        window.draw(_ground.groundSprite);
        _obstacles.draw(window);
        _clouds.draw(window);

        // Draw score and high score
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