#include "dino.h"
#include "sounds.h"


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
        std::cerr << "[ERROR] Error loading the PlayerSprite texture" << std::endl;
    }
}

void Dino::update(sf::Time& deltaTime, float gameSpeed)
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
        walk(gameSpeed);  // Call the regular walking animation
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && dinoPos.y >= window_height - 150.f)
    {
        animationCounter = 0;
        dinoMotion.y = -10.f;
        dino.setTextureRect(frames[1]);

        // play jump sound
        _sounds.jumpSound.play();
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

void Dino::walk(float gameSpeed) {
    // Calculate interval based on gameSpeed; the higher the gameSpeed, the lower the interval
    int animationInterval = static_cast<int>(18 / gameSpeed);

    // Cycle between frames 1 and 2 based on the calculated interval
    if (animationCounter % animationInterval < animationInterval / 2) {
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

sf::FloatRect Dino::getCollisionBounds() const {
    sf::FloatRect bounds = dino.getGlobalBounds();
    bounds.left += 10.f;     // Shrink the left side
    bounds.width -= 20.f;    // Shrink width from both sides
    bounds.top += 5.f;       // Shrink the top side
    bounds.height -= 10.f;   // Shrink height from both top and bottom
    return bounds;
}

void Dino::reset() {
    animationCounter = 0;
    dino.setTextureRect(frames[0]);
    dino.setPosition(50.f, groundOffset);
}