#include "game.h"

int main() 
{
    sf::RenderWindow window;

    window.create(sf::VideoMode(window_width, window_height), "Dino Game", sf::Style::Close);
    window.setVerticalSyncEnabled(true);

    // initiate game
    Game game;

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

        game.update(deltaTime);

        window.clear(sf::Color::White);

        // draw game objects on screen
        game.draw(window);

        // end the current frame
        window.display();
    }

    return 0;
}
