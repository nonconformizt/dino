
#include "Cactus.hpp"

Cactus::Cactus(sf::Vector2f pos)
{
    texture.loadFromFile("assets/cactus.png");
    sprite.setTexture(texture);
    sprite.setTextureRect(sf::IntRect(0, 0, CACTUS_W, CACTUS_H));
    sprite.setPosition(pos.x, LVL_H - pos.y - CACTUS_H);
}

bool Cactus::collision(sf::FloatRect player)
{
    // ???
    player.left += 10;
    player.top += 10;
    player.height -= 10;
    player.width -= 10;

    return sprite.getGlobalBounds().intersects(player);
}

void Cactus::update() {
    // never gonna be used
}
