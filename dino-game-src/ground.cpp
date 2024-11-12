#include "ground.h"

Ground::Ground() {
    if (groundTexture.loadFromFile("../assets/spritesheets/ground.png")) {
        groundSprite.setTexture(groundTexture);
        groundSprite.setPosition(sf::Vector2f(0.0f, (window_height + 0.0f) - groundTexture.getSize().y - 50.0f));
    }
    else
        std::cerr << "Cannot load ground spritesheet. Read SFML error for more information" << std::endl;
}

void Ground::update() {
    if (offset > groundTexture.getSize().x - window_width)
        offset = 0;
    
    offset += gameSpeed;

    groundSprite.setTextureRect(sf::IntRect(offset, 0, window_width, window_height));
}