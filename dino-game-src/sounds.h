#pragma once

#include "core.h"

class Sounds {
private:
	sf::SoundBuffer _die_sbuffer;
	sf::SoundBuffer _jump_sbuffer;
	sf::SoundBuffer _point_sbuffer;

public:
	sf::Sound dieSound;
	sf::Sound jumpSound;
	sf::Sound pointSound;

	// constructor
	Sounds() {
		if (!_die_sbuffer.loadFromFile("../assets/sounds/die.wav"))
			std::cerr << "[ERROR] Cannot load 'die.wav'. Read SFML error for more information" << std::endl;
		if (!_jump_sbuffer.loadFromFile("../assets/sounds/jump.wav"))
			std::cerr << "[ERROR] Cannot load 'jump.wav'. Read SFML error for more information" << std::endl;
		if (!_point_sbuffer.loadFromFile("../assets/sounds/point.wav"))
			std::cerr << "[ERROR] Cannot load 'point.wav'. Read SFML error for more information" << std::endl;

		dieSound.setBuffer(_die_sbuffer);
		jumpSound.setBuffer(_jump_sbuffer);
		pointSound.setBuffer(_point_sbuffer);
	}
};