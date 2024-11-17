#pragma once

#include "core.h"

class Button
{
private:
	sf::Sprite _btnSprite;
	sf::Texture _btnTexture;

public:
	// constructor
	Button() {
		if (_btnTexture.loadFromFile("../assets/spritesheets/restart_button.png"))
			_btnSprite.setTexture(_btnTexture);
		_btnSprite.setPosition(
			sf::Vector2f(static_cast<float>(window_width / 2 - (_btnTexture.getSize().x / 2)),
											static_cast<float>(window_height / 2))
		);
		_btnSprite.setScale(sf::Vector2f(0.75f, 0.75f));
	}

	// destructor
	~Button() {}

	// getters
	float getButtonBoundW() { return _btnSprite.getGlobalBounds().width; }

	float getButtonBoundH() { return _btnSprite.getGlobalBounds().height; }

	// setters
	void setButtonPosition(sf::Vector2f& position) {
		_btnSprite.setPosition(position);
	}

	void draw(sf::RenderWindow& window) {
		window.draw(_btnSprite);
	}

	float getPositionX() { return _btnSprite.getPosition().x; }

	float getPositionY() { return _btnSprite.getPosition().y; }
};