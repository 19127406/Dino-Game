#pragma once

#include "core.h"
#include "dino.h"
#include "random.h"

#include <vector>
//#include <random>
#include <array>
#include <string>

class Obstacle {
public:
	sf::Sprite obstacleSprite;
};

class Cactus : public Obstacle {
public:
	Cactus(sf::Texture& texture) {
		obstacleSprite.setTexture(texture);
		obstacleSprite.setPosition(sf::Vector2f(window_width, groundOffset));
	}
};

class Bird : public Obstacle {
private:
	sf::FloatRect _birdBounds;
	std::array<sf::IntRect, 2> _frames;
	int _animationCounter = 0;

public:
	Bird(sf::Texture& texture, sf::Vector2f initPosition) {
		obstacleSprite.setTexture(texture);

		for (int i = 0; i < _frames.size(); i++)
			_frames[i] = sf::IntRect(i * 90, 0, 90, 80);

		obstacleSprite.setTextureRect(_frames[0]);
		obstacleSprite.setPosition(initPosition);
	}

	void fly() {
		if (_animationCounter % 50 < 25)
			obstacleSprite.setTextureRect(_frames[1]);
		else
			obstacleSprite.setTextureRect(_frames[0]);
		
		if (_animationCounter < 200)
			_animationCounter++;
		else
			_animationCounter = 0;
	}
};

class Obstacles {
private:
	std::vector<Cactus> _obstacles;
	std::vector<Bird> _birds;
	sf::Texture _cactus_single;
	sf::Texture _cactus_group;
	sf::Texture _cactus_big;
	sf::Texture _bird;
	sf::Time _spawnTimer;

	// randomize bird spawn position
	Random _randomPos{ window_height / 2, window_height / 2 + 150 };
	// randomize which obstacle will be spawned
	Random _randomObs{ 1, 4 };

public:
	// constructor
	Obstacles();

	void update(sf::Time& deltaTime);
	void draw(sf::RenderWindow& window);
	bool checkCollision(const Dino& dino);
};