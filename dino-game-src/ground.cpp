#include "ground.h"

Ground::Ground() {
    if (_groundTexture.loadFromFile("../assets/spritesheets/ground.png")) {
        groundSprite.setTexture(_groundTexture);
        groundSprite.setPosition(sf::Vector2f(0.0f, (window_height + 0.0f) - _groundTexture.getSize().y - 50.0f));
    }
    else
        std::cerr << "[ERROR] Cannot load ground spritesheet. Read SFML error for more information" << std::endl;

    if (!_bg_music.openFromFile("../assets/sounds/yoasobi_yoru_kakeru.wav"))
        std::cerr << "[ERROR] Cannot load background music. Read SFML error for more information" << std::endl;
    _bg_music.setVolume(50.0f);
    startMusic();
}

Ground::~Ground() {
    stopMusic();
}

void Ground::update(float gameSpeed) {
    if (_offset > _groundTexture.getSize().x - window_width)
        _offset = 0;
    
    _offset += _base_speed * gameSpeed;

    groundSprite.setTextureRect(sf::IntRect(_offset, 0, window_width, window_height));
}

void Ground::startMusic() {
    _bg_music.play();
}

void Ground::stopMusic() {
    _bg_music.stop();
}

void Ground::reset() {
    _offset = 0;
    groundSprite.setTextureRect(sf::IntRect(0, 0, window_width, window_height));
    startMusic();
}