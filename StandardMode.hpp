//
// Created by nonconformist on 12.05.2019.
//

#ifndef DINO_STANDARDMODE_HPP
#define DINO_STANDARDMODE_HPP

#include <iostream>
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

private:
    void initObjects();
    void redrawTiles();
    float checkMovement(sf::RectangleShape rect, float offset);

    sf::RenderWindow * window;
    sf::Texture platformTexture;

    // view movement for standard mode is much simpler,
    // so no need to use Camera class
    sf::View view;

    std::vector<sf::Sprite> platforms;
    Player player;
    float playerOffset;
    std::vector<Cactus> cactuses;
    std::vector<Pterodactyl> pteros;
    sf::RectangleShape background;

    float velocity = 3.0;

};


#endif //DINO_STANDARDMODE_HPP
