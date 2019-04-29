
#include "Missile.hpp"

Missile::Missile()
{
    texture.loadFromFile("assets/missile.png");

    sprite.setTexture(texture);
    sprite.setTextureRect(sf::IntRect(0, 0, 67, 23));

    rect.setSize(sf::Vector2f(67, 23));
    rect.setPosition(350, 200);
}

void Missile::update()
{
    rect.move(speed, 0);

    sprite.setTextureRect(sf::IntRect((walk_counter/5)*67, 0, 67, 23));
    sprite.setPosition(rect.getPosition());

    walk_counter = (++walk_counter) % 20;
}
