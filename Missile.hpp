
#ifndef DINO_MISSILE_HPP
#define DINO_MISSILE_HPP

#include "Entity.hpp"

class Missile : public Entity {

public:
    Missile();
    void update() final;

private:
    double speed = 5.0;
    int direction = 1; // -1 for left; 1 for right
};


#endif //DINO_MISSILE_HPP
