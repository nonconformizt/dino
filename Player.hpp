
#ifndef DINO_PLAYER_HPP
#define DINO_PLAYER_HPP

#include "Entity.hpp"
#include <iostream>

class Player : public Entity {

public:
    Player();
    void update() final;

private:
    double speed = 3.0;
    bool down = false,
         left = false;
};


#endif //DINO_PLAYER_HPP
