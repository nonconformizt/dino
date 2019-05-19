
#include "Coin.hpp"

Coin::Coin(sf::Vector2f pos)
{
    texture.loadFromFile("assets/coin.png");
    sprite.setTexture(texture);
    sprite.setTextureRect(sf::IntRect(0, 0, 18, 18));
    sprite.setPosition(pos);
}

void Coin::update()
{
    sprite.setTextureRect(sf::IntRect(walk_counter/5 * 18, 0, 18, 18));
    walk_counter = (++walk_counter) % 40;
}
