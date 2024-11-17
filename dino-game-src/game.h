#pragma once

#include "dino.h"
#include "ground.h"
#include "obstacles.h"
#include "clouds.h"
#include "buttons.h"
#include "texts.h"
#include "ScoreManager.h"

class Game {
private:
    Dino _dino;
    Ground _ground;
    Obstacles _obstacles;
    Clouds _clouds;
    Button _restartButton;

    Text _overlayText;
    Text _instructionText;
    ScoreManager _scoreManager;
    sf::Clock _scoreClock;  // To track score update intervals

    float _gameSpeedDino = 1.0f;
    float _gameSpeedObs = 1.0f;
    const float _speedIncrementDino = 0.01f;
    const float _speedIncrementObs = 0.0005f;//<--Adjust this to increase obstacle speed increasement

    bool _inGame = false;

public:
    // constructor
    Game();

    // destructor
    ~Game();

    void update(sf::Time& deltaTime);
    void draw(sf::RenderWindow& window);
};