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

int Obstacles::update(sf::Time& deltaTime, float gameSpeed) {
    int avoidedCount = 0;  // Counter for avoided obstacles

    _spawnTimer += deltaTime;

    if (_spawnTimer.asSeconds() > (1.0f + gameSpeed / static_cast<float>(3))) {
        // Spawn new obstacle
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
            _birds.emplace_back(Bird(_bird, sf::Vector2f(window_width,
                static_cast<float>(_randomPos()))));
            break;
        default:
            break;
        }

        _spawnTimer = sf::Time::Zero;
    }

    // Update cactus positions
    for (int i = 0; i < _obstacles.size(); i++) {
        _obstacles[i].obstacleSprite.move(-3 * gameSpeed, 0.0f);

        if (_obstacles[i].obstacleSprite.getPosition().x < -150.0f) {
            // Remove obstacle and count as avoided
            _obstacles.erase(_obstacles.begin() + i);
            avoidedCount++;
        }
    }

    // Update bird positions
    for (int i = 0; i < _birds.size(); i++) {
        _birds[i].fly();
        _birds[i].obstacleSprite.move(-3 * gameSpeed, 0.0f);

        if (_birds[i].obstacleSprite.getPosition().x < -150.0f) {
            // Remove bird and count as avoided
            _birds.erase(_birds.begin() + i);
            avoidedCount++;
        }
    }

    return avoidedCount;
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
