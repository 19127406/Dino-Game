#pragma once

#include "core.h"


class Ground {
private:
    sf::Texture _groundTexture;
    sf::Music _bg_music;
    int _offset = 0;

public:
    sf::Sprite groundSprite;

    // constructor
    Ground();

    // destructor
    ~Ground();

    void update();
    void startMusic();
    void stopMusic();
    void reset();
};