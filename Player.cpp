
#include "Player.hpp"

Player::Player()
{
    texture.loadFromFile("assets/player_v2.png");

    sprite.setTexture(texture);
    sprite.setTextureRect(sf::IntRect(0, 0, 64, 72));

    rect.setSize(sf::Vector2f(64, 72));
    rect.setPosition(300, 200);
}

void Player::update()
{

    if ( !down && sf::Keyboard::isKeyPressed(sf::Keyboard::S) ) {
        // пригнуься
        rect.setSize(sf::Vector2f(83, 39));
        rect.move(0, 72 - 39);
        down = true;
    }
    else if ( down && !sf::Keyboard::isKeyPressed(sf::Keyboard::S) ) {
        // выпрямиться
        rect.setSize(sf::Vector2f(64, 72));
        rect.move(0, 39 - 72);
        down = false;
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
        // идти влево
        if (down)
            sprite.setTextureRect(sf::IntRect((walk_counter / 5)*83, 144 + 39, 83, 39));
        else
            sprite.setTextureRect(sf::IntRect((walk_counter / 5)*64, 72, 64, 72));

        left = true;
        rect.move(-speed, 0);
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
        // идти вправо
        if (down)
            sprite.setTextureRect(sf::IntRect((walk_counter / 5)*83, 144, 83, 39));
        else
            sprite.setTextureRect(sf::IntRect((walk_counter / 5)*64, 0, 64, 72));

        left = false;
        rect.move(speed, 0);
    }
    else {
        // стоять на месте
        if (left) {
            if (down)
                sprite.setTextureRect(sf::IntRect(0, 144 + 39, 83, 39));
            else
                sprite.setTextureRect(sf::IntRect(0, 72, 64, 72));
        }
        else {
            if (down)
                sprite.setTextureRect(sf::IntRect(0, 144, 83, 39));
            else
                sprite.setTextureRect(sf::IntRect(0, 0, 64, 72));
        }
    }

    walk_counter = (++walk_counter) % 10; // hehe, funny thing


    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
        spacePressed = true;
    else if (spacePressed) {
        spacePressed = false;
        fire();
    }

    sprite.setPosition(rect.getPosition());
}

void Player::fire()
{
    auto m = new Missile(rect.getPosition(), left ? -1 : 1);
    missiles.push_back(*m);
}
