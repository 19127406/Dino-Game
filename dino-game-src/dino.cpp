#include "dino.h"
#include "sounds.h"


Dino::Dino()
{
    if (_dinoTex.loadFromFile("../assets/spritesheets/dino.png"))
    {
        dino.setTexture(_dinoTex);
        for (int i = 0; i < _frames.size(); i++)
            _frames[i] = sf::IntRect(i * 90, 0, 90, 95);
        dino.setTextureRect(_frames[0]);
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

    _dinoPos = dino.getPosition();
    _dinoBounds = dino.getGlobalBounds();
    _dinoBounds.height -= 15.f;
    _dinoBounds.width -= 10.f;
    _timeTracker += deltaTime;

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
        _isLow = true;
        low();  // Call the bowing animation function
    }
    else {
        _isLow = false;
        walk(gameSpeed);  // Call the regular walking animation
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && _dinoPos.y >= window_height - 150.f)
    {
        animationCounter = 0;
        _dinoMotion.y = -10.f;
        dino.setTextureRect(_frames[1]);

        // play jump sound
        _sounds.jumpSound.play();
    }

    if (_dinoPos.y < window_height - 150.f)
    {
        _dinoMotion.y += 0.15f;
        dino.setTextureRect(_frames[1]);
    }

    if (_dinoPos.y > window_height - 150.f)
    {
        dino.setPosition(sf::Vector2f(dino.getPosition().x, window_height - 150.f));
        _dinoMotion.y = 0.f;
    }

    dino.move(_dinoMotion);
}

void Dino::walk(float gameSpeed) {
    // Calculate interval based on gameSpeed; the higher the gameSpeed, the lower the interval
    int animationInterval = static_cast<int>(18 / gameSpeed);

    // Cycle between frames 1 and 2 based on the calculated interval
    if (animationCounter % animationInterval < animationInterval / 2) {
        dino.setTextureRect(_frames[1]);
    }
    else {
        dino.setTextureRect(_frames[2]);
    }

    animationCounter++;
}

void Dino::low() 
{
    if (animationCounter % 18 < 9) 
    {
        dino.setTextureRect(_frames[4]);
    }
    else {
        dino.setTextureRect(_frames[5]);
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
    dino.setTextureRect(_frames[0]);
    dino.setPosition(50.f, groundOffset);
}