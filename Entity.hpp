
#ifndef DINO_ENTITY_HPP
#define DINO_ENTITY_HPP

#include <SFML/Graphics.hpp>

class Entity {

public:
    sf::RectangleShape rect;
    sf::Texture texture;
    sf::Sprite sprite;
    sf::Text text;

};


#endif //DINO_ENTITY_HPP
