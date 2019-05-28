//
// Created by nonconformist on 12.05.2019.
//

#ifndef DINO_STANDARDMODE_HPP
#define DINO_STANDARDMODE_HPP

#include <iostream>
#include <random>
#include <ctime>
#include <SFML/Graphics.hpp>
#include "Entity.hpp"
#include "Player.hpp"
#include "Cactus.hpp"
#include "Camera.hpp"
#include "Pterodactyl.hpp"

#define A 0.001
#define GROUND (TILE_H * 50)

class StandardMode {

public:
    explicit StandardMode(sf::RenderWindow * win);
    void update();
    void reset() {};

private:
    void initObjects();
    void redrawTiles();
    void updateScore();
    float checkMovement(const sf::RectangleShape * rect, float offset);
    int random(int a, int b);

    sf::RenderWindow * window;
    sf::Texture platformTexture;

    // view movement for standard mode is much simpler,
    // so no need to use Camera class
    sf::View view;

    std::vector<sf::Sprite> platforms;
    Player player;
    float playerOffset = 0;
    std::vector<Cactus> cactuses;
    std::vector<Pterodactyl> pteros;
    sf::RectangleShape background;
    sf::Font font;
    sf::Text score;

    float velocity = 6.0;

    // map generation

    float distance = velocity * 30  ; // minimal distance between cactuses
    float lastCactusX = 0;
    float lastPteroX = 0;
    std::mt19937 mt; // for c++11 random library


};


#endif //DINO_STANDARDMODE_HPP
