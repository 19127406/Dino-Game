#pragma once

#include "core.h"

class Text {
private:
	sf::Font _font;
	sf::Text _text;

public:
	// constructor
	Text() {
		if (_font.loadFromFile("../assets/fonts/press_start_2p.ttf")) {
			_text.setFont(_font);
			_text.setFillColor(sf::Color(61, 61, 61));
			_text.setPosition(
				sf::Vector2f(static_cast<float>(window_width / 2),
							static_cast<float>(window_height / 2))
			);
		}
	}

	// destructor
	~Text() {}

	// getters
	float getTextBoundW() { return _text.getGlobalBounds().width; }

	float getTextBoundH() { return _text.getGlobalBounds().height; }

	// setters
	void setText(std::string text) { _text.setString(text); }

	void setTextSize(unsigned int size) { _text.setCharacterSize(size); }

	void setTextPosition(float x, float y) {
		_text.setPosition(sf::Vector2f(x, y));
	}

	void draw(sf::RenderWindow& window) { window.draw(_text); }
};