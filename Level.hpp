
#ifndef DINO_LEVEL_HPP
#define DINO_LEVEL_HPP

#include <iostream>
#include <SFML/Graphics.hpp>

class Level {

public:
    Level();
    sf::RectangleShape checkMovement(sf::RectangleShape next, sf::RectangleShape curr);

    std::vector<sf::RectangleShape> platforms;


private:
    void loadFromFile();

    int tiles[60][33] = {{0}};


};


#endif //DINO_LEVEL_HPP
