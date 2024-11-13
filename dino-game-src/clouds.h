#pragma once

#include "core.h"

#include <vector>
#include <random>

class Clouds
{
private:
	std::vector<sf::Sprite> _clouds;
	sf::Texture _cloudTexture;
	sf::Time _currentTime;

	// random engine
	std::random_device _rdev;
	std::mt19937 _mt{ _rdev() };
	std::uniform_int_distribution<std::mt19937::result_type> _dist{ window_height / 2 - 200, window_height / 2 - 50 };

public:
	// constructor
	Clouds();

	void update(sf::Time& deltaTime);
	void draw(sf::RenderWindow& window);
};