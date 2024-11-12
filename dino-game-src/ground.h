#pragma once

#include "core.h"


class Ground {
private:
    sf::Texture groundTexture;
    int offset = 0;

public:
    sf::Sprite groundSprite;

    // constructor
    Ground();

    void update();
};