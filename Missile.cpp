
#include <iostream>
#include "Missile.hpp"

Missile::Missile(sf::Vector2f pos, int dir)
{
    direction = dir;
    texture.loadFromFile("assets/missile.png");

    sprite.setTexture(texture);
    sprite.setTextureRect(sf::IntRect(0, (direction == -1) ? 23 : 0, 67, 23));

    pos.x += dir * 30;
    rect.setSize(sf::Vector2f(67, 23));
    rect.setPosition(pos);
}

void Missile::update()
{
    rect.move(speed * direction, 0);

    sprite.setTextureRect(sf::IntRect((walk_counter/5)*67, (direction == -1) ? 23 : 0, 67, 23));
    sprite.setPosition(rect.getPosition());

    walk_counter = (++walk_counter) % 20;
}
