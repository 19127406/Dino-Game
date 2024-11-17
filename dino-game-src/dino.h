#pragma once

#include "core.h"
#include "sounds.h"

#include <array>
#include <vector>
#include <random>


class Dino {
private:
    sf::Vector2f _dinoPos{ 0.f, 0.f };
    sf::Vector2f _dinoMotion{ 0.f, 0.f };
    sf::Texture _dinoTex;
    sf::FloatRect _dinoBounds;
    std::array<sf::IntRect, 6> _frames;
    sf::Time _timeTracker;

    int animationCounter{ 0 };
    bool _isDead = false;
    bool _isLow = false;

    Sounds _sounds;

public:
    sf::Sprite dino;
    bool isDead() const { return _isDead; }
    void setDead(bool dead)
    {
        _isDead = dead;
        if (_isDead)
        {
            _sounds.dieSound.play();
            dino.setTextureRect(_frames[3]);
        }
    }

    // constructor
    Dino();

    void update(sf::Time& deltaTime, float gameSpeed);
    void walk(float gameSpeed);
    void low();
    sf::FloatRect getCollisionBounds() const;
    void reset();
};