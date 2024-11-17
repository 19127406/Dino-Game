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
        // update game objects
        if (!_dino.isDead())
        {
            // Update game speed gradually over time
            _gameSpeed += _speedIncrement * deltaTime.asSeconds();

            _dino.update(deltaTime, _gameSpeed);
            _ground.update();
            _obstacles.update(deltaTime);

            // check if dino collide with obstacle
            if (_obstacles.checkCollision(_dino))
            {
                _ground.stopMusic();
                _dino.setDead(true);
            }
        }
        else {
            _overlayText.setText("GAME OVER");
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
                _dino.setDead(false);

                _dino.reset();
                _ground.reset();
                _obstacles.reset();
            }
        }
    }
    else {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
            _inGame = true;
    }

    // clouds will still moving even when dino is dead
    // because why would the world stop moving when a little dino gone? (a bit dark here :>)
    _clouds.update(deltaTime);
}

void Game::draw(sf::RenderWindow& window) {
    if (_inGame) {
        window.draw(_dino.dino);
        window.draw(_ground.groundSprite);
        _obstacles.draw(window);
        _clouds.draw(window);

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