#include "dino.h"
#include "ground.h"
#include "obstacles.h"
#include "clouds.h"

int main() 
{

    float gameSpeed = 1.0f;
    const float speedIncrement = 0.01f;

    sf::RenderWindow window;

    window.create(sf::VideoMode(window_width, window_height), "Dino Game", sf::Style::Close);
    window.setVerticalSyncEnabled(true);

    // initiate game objects
    Dino dino;
    Ground ground;
    Obstacles obstacles;
    Clouds clouds;

    // check all the window's events that were triggered since the last iteration of the loop
    sf::Event event;
    sf::Clock deltaTimeClock;
    sf::Time deltaTime;

    // start render loop
    while (window.isOpen())
    {
        // check if user close the game window
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        deltaTime = deltaTimeClock.restart();

        // Update game speed gradually over time
        gameSpeed += speedIncrement * deltaTime.asSeconds(); // Adjust increment as needed

        // update game objects
        if (!dino.isDead())
        {
            dino.update(deltaTime, gameSpeed);
            ground.update();
            obstacles.update(deltaTime);

            if (obstacles.checkCollision(dino))
            {
                dino.setDead(true);
            }
        }
        // clouds will still moving even when dino is dead
        // because why would the world stop moving when a little dino gone? (a bit dark here :>)
        clouds.update(deltaTime);

        window.clear(sf::Color::White);

        // draw objects on screen
        window.draw(dino.dino);
        window.draw(ground.groundSprite);
        obstacles.draw(window);
        clouds.draw(window);

        // end the current frame
        window.display();
    }

    return 0;
}
