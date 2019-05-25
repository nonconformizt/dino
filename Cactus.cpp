
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
    float plCenterX = player.left + 32,
          plCenterY = player.top + 36,
          cactCenterX = sprite.getPosition().x + (float) CACTUS_W / 2,
          cactCenterY = sprite.getPosition().y + (float) CACTUS_H / 2;

    return sqrtf((cactCenterX - plCenterX)*(cactCenterX - plCenterX) + (cactCenterY - plCenterY)*(cactCenterY - plCenterY)) < CACTUS_W + 3;
}

void Cactus::update() {
    // never gonna be used
}
