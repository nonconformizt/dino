
#ifndef DINO_PLAYER_HPP
#define DINO_PLAYER_HPP

#include "Entity.hpp"
#include <iostream>

class Player : public Entity {

public:
    Player();
    void update();

private:
    double speed = 3.0;
    int walk_counter = 0;
    bool down = false,
         left = false;
//         right = false;
};


#endif //DINO_PLAYER_HPP
