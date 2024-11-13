#include "obstacles.h"

Obstacles::Obstacles() {
	_spawnTimer = sf::Time::Zero;
	_obstacles.reserve(5);

	if (!_cactus_single.loadFromFile("../assets/spritesheets/cactus_single.png"))
		std::cerr << "Cannot load cactus_single spritesheet" << std::endl;

	if (!_cactus_group.loadFromFile("../assets/spritesheets/cactus_group.png"))
		std::cerr << "Cannot load cactus_group spritesheet" << std::endl;

	if (!_cactus_big.loadFromFile("../assets/spritesheets/cactus_big.png"))
		std::cerr << "Cannot load cactus_big spritesheet" << std::endl;
}

void Obstacles::update(sf::Time& deltaTime) {
	int randomNumber = 0;

	_spawnTimer += deltaTime;

	if (_spawnTimer.asSeconds() > (0.5f + gameSpeed / static_cast<float>(3))) {
		randomNumber = (rand() % 3) + 1;

		switch (randomNumber)
		{
		case 1:
			_obstacles.emplace_back(Obstacle(_cactus_single));
			break;
		case 2:
			_obstacles.emplace_back(Obstacle(_cactus_group));
			break;
		case 3:
			_obstacles.emplace_back(Obstacle(_cactus_big));
			break;
		default:
			break;
		}

		_spawnTimer = sf::Time::Zero;
	}

	for (int i = 0; i < _obstacles.size(); i++) {
		_obstacles[i].obstacleSprite.move(-1 * gameSpeed, 0.0f);
		if (_obstacles[i].obstacleSprite.getPosition().x < -150.0f) {
			std::vector<Obstacle>::iterator iter = _obstacles.begin() + i;
			_obstacles.erase(iter);
		}
	}
}

void Obstacles::draw(sf::RenderWindow& window) {
	for (auto& obstacle : _obstacles)
		window.draw(obstacle.obstacleSprite);
}

bool Obstacles::checkCollision(const Dino& dino) {
	for (const auto& obstacle : _obstacles) {
		if (dino.dino.getGlobalBounds().intersects(obstacle.obstacleSprite.getGlobalBounds())) {
			return true;
		}
	}
	return false;
}
