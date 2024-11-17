#include "obstacles.h"

Obstacles::Obstacles() {
	_spawnTimer = sf::Time::Zero;
	_obstacles.reserve(5);
	_birds.reserve(3);

	if (!_cactus_single.loadFromFile("../assets/spritesheets/cactus_single.png"))
		std::cerr << "[ERROR] Cannot load cactus_single spritesheet" << std::endl;

	if (!_cactus_group.loadFromFile("../assets/spritesheets/cactus_group.png"))
		std::cerr << "[ERROR] Cannot load cactus_group spritesheet" << std::endl;

	if (!_cactus_big.loadFromFile("../assets/spritesheets/cactus_big.png"))
		std::cerr << "[ERROR] Cannot load cactus_big spritesheet" << std::endl;

	if (!_bird.loadFromFile("../assets/spritesheets/bird.png"))
		std::cerr << "[ERROR] Cannot load bird spritesheet" << std::endl;
}

void Obstacles::update(sf::Time& deltaTime, float gameSpeed) {
	_spawnTimer += deltaTime;

	// Dynamic spawn rate based on game speed
	if (_spawnTimer.asSeconds() > (2.0f - gameSpeed * 0.1f)) {
		switch (_randomObs()) {
		case 1:
			_obstacles.emplace_back(Cactus(_cactus_single));
			break;
		case 2:
			_obstacles.emplace_back(Cactus(_cactus_group));
			break;
		case 3:
			_obstacles.emplace_back(Cactus(_cactus_big));
			break;
		case 4:
			_birds.emplace_back(Bird(_bird, sf::Vector2f(window_width, static_cast<float>(_randomPos()))));
			break;
		default:
			break;
		}

		_spawnTimer = sf::Time::Zero;
	}

	// Update positions
	for (int i = 0; i < _obstacles.size(); i++) {
		_obstacles[i].obstacleSprite.move(-3.0f * gameSpeed, 0.0f);

		if (_obstacles[i].obstacleSprite.getPosition().x < -150.0f) {
			_obstacles.erase(_obstacles.begin() + i);
		}
	}

	for (int i = 0; i < _birds.size(); i++) {
		_birds[i].fly();
		_birds[i].obstacleSprite.move(-3.0f * gameSpeed, 0.0f);

		if (_birds[i].obstacleSprite.getPosition().x < -150.0f) {
			_birds.erase(_birds.begin() + i);
		}
	}
}

void Obstacles::draw(sf::RenderWindow& window) {
	for (const auto& obstacle : _obstacles)
		window.draw(obstacle.obstacleSprite);

	for (const auto& bird : _birds)
		window.draw(bird.obstacleSprite);
}

bool Obstacles::checkCollision(const Dino& dino) {
	sf::FloatRect dinoBounds = dino.getCollisionBounds();

	for (const auto& cactus : _obstacles) {
		if (cactus.getCollisionBounds().intersects(dinoBounds)) {
			std::cout << "[INFO] Collision detected with cactus!" << std::endl;
			return true;
		}
	}

	for (const auto& bird : _birds) {
		if (bird.getCollisionBounds().intersects(dinoBounds)) {
			std::cout << "[INFO] Collision detected with bird!" << std::endl;
			return true;
		}
	}

	return false;
}

void Obstacles::reset() {
	_spawnTimer = sf::Time::Zero;
	_obstacles.clear();
	_birds.clear();
}
