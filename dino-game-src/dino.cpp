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
    dinoPos = dino.getPosition();
    dinoBounds = dino.getGlobalBounds();
    dinoBounds.height -= 15.f;
    dinoBounds.width -= 10.f;
    timeTracker += deltaTime;

    walk();

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && dinoPos.y >= window_height - 150.f)
    {
        animationCounter = 0;
        dinoMotion.y = -12.5f;
        dino.setTextureRect(frames[1]);
    }

    if (dinoPos.y < window_height - 150.f)
    {
        dinoMotion.y += 0.25f;
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
    for (int i = 0; i < frames.size() - 3; i++)
        if (animationCounter == (i + 1) * 3)
            dino.setTextureRect(frames[i]);

    if (animationCounter >= (frames.size() - 2) * 8)
        animationCounter = 0;

    animationCounter++;
}