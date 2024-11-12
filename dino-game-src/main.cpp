#include <SFML/Graphics.hpp>
#include <iostream>
#include <array>
#include <vector>
#include <random>

const unsigned int windowSize_x = 1000;
const unsigned int windowSize_y = 500;

class Dino {
public:
    sf::Sprite dino;
    sf::Vector2f dinoPos{ 0.f, 0.f };
    sf::Vector2f dinoMotion{ 0.f, 0.f };
    sf::Texture dinoTex;
    sf::FloatRect dinoBounds;
    std::array<sf::IntRect, 6> frames;
    sf::Time timeTracker;
    int animationCounter{ 0 };

    Dino()
        :dino(), dinoTex(), timeTracker()
    {
        if (dinoTex.loadFromFile("images/PlayerSpriteSheet.png"))
        {
            dino.setTexture(dinoTex);
            for (int i = 0; i < frames.size(); i++)
                frames[i] = sf::IntRect(i * 90, 0, 90, 95);
            dino.setTextureRect(frames[0]);
            dino.setPosition(50.f, windowSize_y - 150.f); // Set initial position of Dino
        }
        else
        {
            std::cout << "Error loading the PlayerSprite texture" << std::endl;
        }
    }

    void update(sf::Time& deltaTime)
    {
        dinoPos = dino.getPosition();
        dinoBounds = dino.getGlobalBounds();
        dinoBounds.height -= 15.f;
        dinoBounds.width -= 10.f;
        timeTracker += deltaTime;

        walk();

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && dinoPos.y >= windowSize_y - 150.f)
        {
            animationCounter = 0;
            dinoMotion.y = -20.f;
            dino.setTextureRect(frames[1]);
        }

        if (dinoPos.y < windowSize_y - 150.f)
        {
            dinoMotion.y += 1.f;
            dino.setTextureRect(frames[1]);
        }

        if (dinoPos.y > windowSize_y - 150.f)
        {
            dino.setPosition(sf::Vector2f(dino.getPosition().x, windowSize_y - 150.f));
            dinoMotion.y = 0.f;
        }

        dino.move(dinoMotion);
    }

    void walk()
    {
        for (int i = 0; i < frames.size() - 3; i++)
            if (animationCounter == (i + 1) * 3)
                dino.setTextureRect(frames[i]);

        if (animationCounter >= (frames.size() - 2) * 5 )
            animationCounter = 0;

        animationCounter++;
    }
};

int main() {
    sf::RenderWindow window(sf::VideoMode(windowSize_x, windowSize_y), "Dino_Game");
    window.setVerticalSyncEnabled(true);

    Dino dino;

    sf::Clock deltaTimeClock;
    sf::Time deltaTime;

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        deltaTime = deltaTimeClock.restart();

        dino.update(deltaTime);

        window.clear(sf::Color::White);
        window.draw(dino.dino);
        window.display();
    }

    return 0;
}
