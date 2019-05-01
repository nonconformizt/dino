
#ifndef DINO_PLAYER_HPP
#define DINO_PLAYER_HPP

#include "Entity.hpp"
#include "Missile.hpp"
#include <iostream>

class Player : public Entity {

public:
    std::vector<Missile> missiles;
    sf::RectangleShape nextPos;
    sf::Vector2f velocity = {0, 0};

    Player();
    void update() final;
    void render(sf::RectangleShape newPos);

private:
    double walkSpeed = 3.0,
           jumpSpeed = 10.0;

    bool down = false, // is player bended down?
         left = false, // is player faced left?
         upPressed = false,
         spacePressed = false;

    void fire();

};


#endif //DINO_PLAYER_HPP
