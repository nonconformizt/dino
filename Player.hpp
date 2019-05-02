
#ifndef DINO_PLAYER_HPP
#define DINO_PLAYER_HPP

#include "Entity.hpp"
#include "Missile.hpp"
#include <iostream>

class Player : public Entity {

public:
    std::vector<Missile> missiles;
    sf::Vector2f velocity = {0, 0};
    float desiredOffestY = 0.0;

    Player();
    void update() final;
    void render(float offset);

private:
    sf::RectangleShape nextPos;
    double walkSpeed = 4.0,
           jumpSpeed = 12.0;
    bool down = false, // is player bended down
         left = false, // is player faced left
         jump = false, // is player in jump
         upPressed = false,
         spacePressed = false;

    void fire();

};


#endif //DINO_PLAYER_HPP
