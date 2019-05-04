
#ifndef DINO_LEVEL_HPP
#define DINO_LEVEL_HPP

#include <iostream>
#include <SFML/Graphics.hpp>
#include "Entity.hpp"
#include "Cactus.hpp"

class Level {

public:
    Level();
    float checkMovement(sf::RectangleShape rect, float offset);

    std::vector<sf::Sprite> platforms;
    std::vector<Cactus> cactuses;
    sf::RectangleShape background;

private:
    void loadFromFile();

    int tiles[LVL_TILES_H][LVL_TILES_W] = {{0}};
    sf::Texture platformTexture;


};


#endif //DINO_LEVEL_HPP
