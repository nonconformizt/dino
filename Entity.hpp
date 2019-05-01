
#ifndef DINO_ENTITY_HPP
#define DINO_ENTITY_HPP

#include <SFML/Graphics.hpp>

#define G 0.2

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
