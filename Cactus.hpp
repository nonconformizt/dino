
#ifndef DINO_CACTUS_HPP
#define DINO_CACTUS_HPP

#include <SFML/Graphics.hpp>
#include "config.h"
#include "Entity.hpp"

#define CACTUS_H 45
#define CACTUS_W 20

class Cactus : public Entity {

public:
    explicit Cactus(sf::Vector2f pos); //! pos is bottom left point, Y is counting from bottom
    bool collision(sf::FloatRect player);
    void update() final;

private:


};


#endif //DINO_CACTUS_HPP
