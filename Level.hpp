
#ifndef DINO_LEVEL_HPP
#define DINO_LEVEL_HPP

#include <iostream>
#include <SFML/Graphics.hpp>
#include "Entity.hpp"

class Level {

public:
    Level();
    float checkMovement(sf::RectangleShape rect, float offset);

    std::vector<sf::Sprite> platforms;


private:
    void loadFromFile();

    int tiles[60][33] = {{0}};
    sf::Texture platformTexture;


};


#endif //DINO_LEVEL_HPP
