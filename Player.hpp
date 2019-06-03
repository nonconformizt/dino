
#ifndef DINO_PLAYER_HPP
#define DINO_PLAYER_HPP

#include "Entity.hpp"
#include "Missile.hpp"
#include <iostream>
#include <SFML/Audio.hpp>

class Player : public Entity {

public:
    std::vector<Missile> missiles;
    sf::Vector2f velocity = {0, 0};
    float desiredOffsetY = 0.0;

    bool dead = false;

    Player();
    void update() final;
    void render(float offset);
    void teleport(sf::Vector2f pos);
    void stop() { velocity.x = velocity.y = 0; };
    void setCharacter(size_t character);
    void setInfiniteMode(bool isInfinite) {infiniteMode = isInfinite; rect.setPosition(50, rect.getPosition().y); }
    void setInfModeSpeed(float speed) {walkSpeed = speed;}

private:
    void fire();

    sf::RectangleShape nextPos;
    float walkSpeed = 5.0,
          jumpSpeed = 12.0;
    bool infiniteMode = false,
         down = false, // is player bended down
         left = false, // is player faced left
         jump = false, // is player in jump
         upPressed = false,
         spacePressed = false;

    sf::SoundBuffer jumpBuf, hitBuf;
    sf::Sound jumpSound, hitSound;

};


#endif //DINO_PLAYER_HPP
