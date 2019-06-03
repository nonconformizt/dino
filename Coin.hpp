#ifndef DINO_COIN_HPP
#define DINO_COIN_HPP

#include "Entity.hpp"

class Coin : public Entity {

public:
    explicit Coin(sf::Vector2f pos);
    void update() final;
    void collect() { shown = false; }
    bool isCollected() { return !shown; }

private:
    bool shown = true;

};


#endif //DINO_COIN_HPP
