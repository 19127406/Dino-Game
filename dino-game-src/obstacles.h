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

	// Virtual function for getting collision bounds
	virtual sf::FloatRect getCollisionBounds() const {
		return obstacleSprite.getGlobalBounds();
	}

	virtual ~Obstacle() = default;  // Virtual destructor for polymorphic class
};

class Cactus : public Obstacle {
public:
	Cactus(sf::Texture& texture) {
		obstacleSprite.setTexture(texture);
		obstacleSprite.setPosition(sf::Vector2f(window_width, groundOffset));
	}

	sf::FloatRect getCollisionBounds() const override {
		sf::FloatRect bounds = obstacleSprite.getGlobalBounds();
		bounds.left += 5.f;    // Adjust as needed
		bounds.width -= 10.f;  // Adjust as needed
		return bounds;
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

	sf::FloatRect getCollisionBounds() const override
	{
		sf::FloatRect bounds = obstacleSprite.getGlobalBounds();
		bounds.top += 5.f;    // Adjust as needed
		bounds.height -= 10.f; // Adjust as needed
		return bounds;
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
	//sf::FloatRect getCollisionBounds() const;
};