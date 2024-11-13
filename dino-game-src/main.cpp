#include "dino.h"
#include "ground.h"
#include "obstacles.h"

int main() {
    sf::RenderWindow window;

    window.create(sf::VideoMode(window_width, window_height), "Dino Game", sf::Style::Close);
    window.setVerticalSyncEnabled(true);

    // initiate game objects
    Dino dino;
    Ground ground;
    Obstacles obstacles;

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

        // update game objects
        if (!dino.isDead())
        {
            dino.update(deltaTime);
            ground.update();
            obstacles.update(deltaTime);

            if (obstacles.checkCollision(dino)) 
            {
                dino.setDead(true);
            }
        }

        window.clear(sf::Color::White);

        // draw objects on screen
        window.draw(dino.dino);
        window.draw(ground.groundSprite);
        obstacles.draw(window);

        // end the current frame
        window.display();
    }

    return 0;
}
