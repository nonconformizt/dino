
#include "Player.hpp"

Player::Player()
{
    texture.loadFromFile("assets/player_v2.png");

    sprite.setTexture(texture);
    sprite.setTextureRect(sf::IntRect(0, 0, 64, 72));
//    sprite.scale(1.5, 1.5);

    rect.setSize(sf::Vector2f(64, 72));
    rect.setPosition(300, 200);
}

void Player::update()
{

//    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {'
//        rect.move(0, -speed);
//        sprite.setTextureRect(sf::IntRect());
//    }
//
//    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
//        rect.move(0, speed);
//        sprite.setTextureRect(sf::IntRect());
//    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
        rect.move(-speed, 0);
        sprite.setTextureRect(sf::IntRect((walk_counter / 5)*64, 72, 64, 72));
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
        rect.move(speed, 0);
        sprite.setTextureRect(sf::IntRect((walk_counter / 5)*64, 0, 64, 72));
    }

    walk_counter = (++walk_counter) % 10; // hehe, funny thing

    sprite.setPosition(rect.getPosition());
}

