#pragma once

#include "core.h"
#include "dino.h"

#include <vector>
#include <random>
#include <array>
#include <string>

class Obstacle {
public:
	sf::Sprite obstacleSprite;

	virtual std::string getObstacleType() = 0;
	virtual void move() {}
};

class Cactus : public Obstacle {
public:
	Cactus(sf::Texture& texture) {
		obstacleSprite.setTexture(texture);
		obstacleSprite.setPosition(sf::Vector2f(window_width, groundOffset));
	}

	std::string getObstacleType() {
		return std::string("cactus");
	}

	void move() override {}
};

class Bird : public Obstacle {
private:
	sf::FloatRect _birdBounds;
	std::array<sf::IntRect, 2> _frames;
	int _animationCounter = 0;

public:
	Bird(sf::Texture& texture) {
		obstacleSprite.setTexture(texture);

		for (int i = 0; i < _frames.size(); i++)
			_frames[i] = sf::IntRect(i * 90, 0, 90, 80);

		obstacleSprite.setTextureRect(_frames[0]);
		obstacleSprite.setPosition(sf::Vector2f(window_width, window_height / 2));
	}

	std::string getObstacleType() {
		return std::string("bird");
	}

	void move() override {
		if (_animationCounter % 18 < 9)
			obstacleSprite.setTextureRect(_frames[1]);
		else
			obstacleSprite.setTextureRect(_frames[0]);
		
		if (_animationCounter < 180)
			_animationCounter++;
		else
			_animationCounter = 0;
	}
};

class Obstacles {
private:
	std::vector<Cactus> _obstacles;
	sf::Texture _cactus_single;
	sf::Texture _cactus_group;
	sf::Texture _cactus_big;
	sf::Texture _bird;
	sf::Time _spawnTimer;

	// random engine
	std::random_device _rdev;
	std::mt19937 _mt{ _rdev() };
	// randomize bird spawn position
	std::uniform_int_distribution<std::mt19937::result_type> _distPos{ window_height / 2 - 200, window_height / 2 - 50 };
	// randomize which obstacle will be spawned
	std::uniform_int_distribution<std::mt19937::result_type> _distObs{ 1, 4 };

public:
	// constructor
	Obstacles();

	void update(sf::Time& deltaTime);
	void draw(sf::RenderWindow& window);
	bool checkCollision(const Dino& dino);
};