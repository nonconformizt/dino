
#ifndef DINO_PTERODACTYL_HPP
#define DINO_PTERODACTYL_HPP

#include "Entity.hpp"

class Pterodactyl : public Entity {

public:
    Pterodactyl(sf::Vector2f pos, float sp);
    void update() final;

private:
    float speed = 3.0;
    int dir = -1; // 1 for right, -1 for left

};


#endif //DINO_PTERODACTYL_HPP
