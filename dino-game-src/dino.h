#pragma once

#include "core.h"

#include <array>
#include <vector>
#include <random>


class Dino {
private:
    sf::Vector2f dinoPos{ 0.f, 0.f };
    sf::Vector2f dinoMotion{ 0.f, 0.f };
    sf::Texture dinoTex;
    sf::FloatRect dinoBounds;
    std::array<sf::IntRect, 6> frames;
    sf::Time timeTracker;
    int animationCounter{ 0 };
    bool _isDead = false;
    bool _isLow = false;

public:
    sf::Sprite dino;
    bool isDead() const { return _isDead; }
    void setDead(bool dead)
    {
        _isDead = dead;
        if (_isDead)
        {
            dino.setTextureRect(frames[3]);
        }
    }

    // constructor
    Dino();

    void update(sf::Time& deltaTime, float gameSpeed);
    void walk(float gameSpeed);
    void low();
    sf::FloatRect getCollisionBounds() const;
};