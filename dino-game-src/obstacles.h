#pragma once

#include "core.h"
#include "dino.h"

#include <vector>
#include <random>

class Obstacle {
public:
	sf::Sprite obstacleSprite;

	// constructor
	Obstacle(sf::Texture& texture) {
		obstacleSprite.setTexture(texture);
		obstacleSprite.setPosition(sf::Vector2f(window_width, groundOffset));
	}
};

class Obstacles {
private:
	std::vector<Obstacle> _obstacles;
	sf::Texture _cactus_single;
	sf::Texture _cactus_group;
	sf::Texture _cactus_big;
	sf::Time _spawnTimer;

public:
	// constructor
	Obstacles();

	void update(sf::Time& deltaTime);
	void draw(sf::RenderWindow& window);
	bool checkCollision(const Dino& dino);
};