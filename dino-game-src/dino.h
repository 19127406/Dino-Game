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

public:
    sf::Sprite dino;
    
    // constructor
    Dino();

    void update(sf::Time& deltaTime);
    void walk();
};