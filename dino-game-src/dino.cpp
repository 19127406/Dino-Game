#include "dino.h"


Dino::Dino()
{
    if (dinoTex.loadFromFile("../assets/spritesheets/dino.png"))
    {
        dino.setTexture(dinoTex);
        for (int i = 0; i < frames.size(); i++)
            frames[i] = sf::IntRect(i * 90, 0, 90, 95);
        dino.setTextureRect(frames[0]);
        dino.setPosition(50.f, groundOffset); // Set initial position of Dino
    }
    else
    {
        std::cerr << "Error loading the PlayerSprite texture" << std::endl;
    }
}

void Dino::update(sf::Time& deltaTime)
{
    if (_isDead) return;

    dinoPos = dino.getPosition();
    dinoBounds = dino.getGlobalBounds();
    dinoBounds.height -= 15.f;
    dinoBounds.width -= 10.f;
    timeTracker += deltaTime;

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
        _isLow = true;
        low();  // Call the bowing animation function
    }
    else {
        _isLow = false;
        walk();  // Call the regular walking animation
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && dinoPos.y >= window_height - 150.f)
    {
        animationCounter = 0;
        dinoMotion.y = -10.f;
        dino.setTextureRect(frames[1]);
    }

    if (dinoPos.y < window_height - 150.f)
    {
        dinoMotion.y += 0.15f;
        dino.setTextureRect(frames[1]);
    }

    if (dinoPos.y > window_height - 150.f)
    {
        dino.setPosition(sf::Vector2f(dino.getPosition().x, window_height - 150.f));
        dinoMotion.y = 0.f;
    }

    dino.move(dinoMotion);
}

void Dino::walk()
{
    if (animationCounter % 18 < 9)
    {
        dino.setTextureRect(frames[1]);
    }
    else {
        dino.setTextureRect(frames[2]);
    }

    animationCounter++;
}

void Dino::low() 
{
    if (animationCounter % 18 < 9) 
    {
        dino.setTextureRect(frames[4]);
    }
    else {
        dino.setTextureRect(frames[5]);
    }
    animationCounter++;
}
