#pragma once

#include "core.h"


class Ground {
private:
    sf::Texture groundTexture;
    sf::Music _bg_music;
    int offset = 0;

public:
    sf::Sprite groundSprite;

    // constructor
    Ground();

    // destructor
    ~Ground();

    void update();
    void startMusic();
    void stopMusic();
};