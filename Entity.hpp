
#ifndef DINO_ENTITY_HPP
#define DINO_ENTITY_HPP

#include "config.h"
#include <SFML/Graphics.hpp>

class Entity {

public:
    sf::RectangleShape rect;
    sf::Texture texture;
    sf::Sprite sprite;

    virtual void update() = 0;

protected:
    int walk_counter = 0;

};


#endif //DINO_ENTITY_HPP
