#include "clouds.h"

Clouds::Clouds() {
	_currentTime = sf::Time::Zero;

	if (_cloudTexture.loadFromFile("../assets/spritesheets/clouds.png")) {
		_clouds.reserve(4);
		_clouds.emplace_back(sf::Sprite(_cloudTexture));
		_clouds.back().setPosition(sf::Vector2f(window_width, window_height / 2 - 40.0f));
	}
	else
		std::cerr << "Cannot load ground spritesheet. Read SFML error for more information" << std::endl;
}

void Clouds::update(sf::Time& deltaTime) {
	_currentTime += deltaTime;
	if (_currentTime.asSeconds() > 8.0f) {
		_clouds.emplace_back(sf::Sprite(_cloudTexture));
		_clouds.back().setPosition(sf::Vector2f( window_width, static_cast<float>(_randomPos()) ));

		_currentTime = sf::Time::Zero;
	}

	for (int i = 0; i < _clouds.size(); i++) {
		_clouds[i].move(sf::Vector2f(-1.0f, 0.0f));

		if (_clouds[i].getPosition().x < 0.0f - _cloudTexture.getSize().x) {
			std::vector<sf::Sprite>::iterator iter = _clouds.begin() + i;
			_clouds.erase(iter);
		}
	}
}

void Clouds::draw(sf::RenderWindow& window) {
	for (auto& cloud : _clouds)
		window.draw(cloud);
}