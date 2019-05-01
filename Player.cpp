
#include "Player.hpp"

Player::Player()
{
    texture.loadFromFile("assets/player.png");

    sprite.setTexture(texture);
    sprite.setTextureRect(sf::IntRect(0, 0, 64, 72));

    rect.setSize(sf::Vector2f(64, 72));
    rect.setPosition(0, 408);
    nextPos.setSize(sf::Vector2f(64, 72));
    nextPos.setPosition(0, 408);
//    velocity.y += - jumpSpeed;
}

void Player::update()
{

    if ( !down && sf::Keyboard::isKeyPressed(sf::Keyboard::S) ) {
        // пригнуься
        nextPos.setSize(sf::Vector2f(83, 39));
        nextPos.move(0, 72 - 39);
        down = true;
    }
    else if ( down && !sf::Keyboard::isKeyPressed(sf::Keyboard::S) ) {
        // выпрямиться
        nextPos.setSize(sf::Vector2f(64, 72));
        nextPos.move(0, 39 - 72);
        down = false;
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
        // идти влево
        if (down)
            sprite.setTextureRect(sf::IntRect((walk_counter / 5)*83, 144 + 39, 83, 39));
        else
            sprite.setTextureRect(sf::IntRect((walk_counter / 5)*64, 72, 64, 72));

        velocity.x = -walkSpeed;
        left = true;
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
        // идти вправо
        if (down)
            sprite.setTextureRect(sf::IntRect((walk_counter / 5)*83, 144, 83, 39));
        else
            sprite.setTextureRect(sf::IntRect((walk_counter / 5)*64, 0, 64, 72));

        velocity.x = walkSpeed;
        left = false;
    }
    else {
        // стоять на месте
        velocity.x = 0;

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

    // JUMP
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
        if (!upPressed) {
            std::cout << "JUMP!\n";
             velocity.y = - jumpSpeed;
        }
        upPressed = true;
    }
    else
        upPressed = false;

    // FIRE!!!!
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
        if (!spacePressed)
            fire();
        spacePressed = true;
    }
    else
        spacePressed = false;


    // apply gravity
    velocity.y += G;

    /**
     *  HANDLE COLLISION
     *  SOMWHERE IN HERE
     */

    nextPos.move(velocity);
}

void Player::fire()
{
    auto m = new Missile(rect.getPosition(), left ? -1 : 1);
    missiles.push_back(*m);
}

void Player::render(sf::RectangleShape newPos)
{
    // detect stop
    if (newPos.getPosition().y == rect.getPosition().y)
        velocity.y = 0;

    rect = newPos;
//    std::cout << newPos.getPosition().x << "; " << newPos.getPosition().y << std::endl;
    sprite.setPosition(rect.getPosition());

}


