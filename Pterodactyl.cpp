
#include <cmath>
#include "Pterodactyl.hpp"

Pterodactyl::Pterodactyl(sf::Vector2f pos, float sp)
{
    speed = sp > 0 ? sp : -sp;
    dir = (sp > 0) ? 1 : -1;

    texture.loadFromFile("assets/ptero.png");

    sprite.setTexture(texture);
    sprite.setTextureRect(sf::IntRect(0, 0, 61, 56));

    rect.setSize(sf::Vector2f(61, 56));
    rect.setPosition(pos);
}

bool Pterodactyl::collision(sf::FloatRect player)
{
    player.left += 10;
    player.top += 0;
    player.height -= 20;
    player.width -= 20;

    return sprite.getGlobalBounds().intersects(player);
}

void Pterodactyl::update()
{
    rect.move(dir * speed, 0);

    if (dead)
        rect.move(0, 10);

    if (((rect.getPosition().x < -100) || (rect.getPosition().x > LVL_W+100)) && !standardMode)
        dir *= -1;


    if (dir == 1)
        sprite.setTextureRect(sf::IntRect(walk_counter/15 * 61, 56, 61, 56));
    else
        sprite.setTextureRect(sf::IntRect(walk_counter/15 * 61, 0, 61, 56));

    sprite.setPosition(rect.getPosition());

    walk_counter = (++walk_counter) % 30;
}
