#pragma once

#include "dino.h"
#include "ground.h"
#include "obstacles.h"
#include "clouds.h"
#include "buttons.h"
#include "texts.h"

class Game {
private:
    Dino _dino;
    Ground _ground;
    Obstacles _obstacles;
    Clouds _clouds;
    Button _restartButton;

    Text _overlayText;
    Text _instructionText;

    float _gameSpeed = 1.0f;
    const float _speedIncrement = 0.01f;

    bool _inGame = false;

public:
    // constructor
    Game();

    // destructor
    ~Game();

    void update(sf::Time& deltaTime);
    void draw(sf::RenderWindow& window);
};