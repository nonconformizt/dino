#ifndef DINO_COIN_HPP
#define DINO_COIN_HPP

#include "Entity.hpp"

class Coin : public Entity {

public:
    Coin(sf::Vector2f pos);
    void update() final;

private:


};


#endif //DINO_COIN_HPP
