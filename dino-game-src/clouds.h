#pragma once

#include "core.h"
#include "random.h"

#include <vector>

class Clouds
{
private:
	std::vector<sf::Sprite> _clouds;
	sf::Texture _cloudTexture;
	sf::Time _currentTime;

	// random clouds spawn position
	Random _randomPos{ window_height / 2 - 200, window_height / 2 - 50 };

public:
	// constructor
	Clouds();

	void update(sf::Time& deltaTime);
	void draw(sf::RenderWindow& window);
};