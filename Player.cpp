
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
}

void Player::update()
{
    // JUMP
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
        if (!upPressed && !jump ) { // can`t jump in flight
            jump = true;
            velocity.y = - jumpSpeed;
        }
        upPressed = true;
    }
    else
        upPressed = false;

    if ( !down && sf::Keyboard::isKeyPressed(sf::Keyboard::S) ) {
        // bend down
        nextPos.setSize(sf::Vector2f(83, 39));
        rect.setSize(sf::Vector2f(83, 39));
        nextPos.move(0, 72 - 39);
        rect.move(0, 72 - 39);
        down = true;
    }
    else if ( down && !sf::Keyboard::isKeyPressed(sf::Keyboard::S) ) {
        // stand straight
        nextPos.setSize(sf::Vector2f(64, 72));
        rect.setSize(sf::Vector2f(64, 72));
        nextPos.move(0, 39 - 72);
        rect.move(0, 39 - 72);
        down = false;
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) && !jump) {
        // go left
        if (down)
            sprite.setTextureRect(sf::IntRect((walk_counter / 5)*83, 144 + 39, 83, 39));
        else
            sprite.setTextureRect(sf::IntRect((walk_counter / 5)*64, 72, 64, 72));

        velocity.x = -walkSpeed;
        left = true;
    }
    // in standard mode u r walking right permanently
    else if ((sf::Keyboard::isKeyPressed(sf::Keyboard::D) || standardMode) && !jump) {
        // go right
        if (down)
            sprite.setTextureRect(sf::IntRect((walk_counter / 5)*83, 144, 83, 39));
        else
            sprite.setTextureRect(sf::IntRect((walk_counter / 5)*64, 0, 64, 72));

        velocity.x = walkSpeed;
        left = false;
    }
    else {
        // stand still

        if (!jump && !standardMode) // keep horizontal speed in flight and in standard mode
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

    // FIRE!!!!
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && !standardMode) {
        if (!spacePressed)
            fire();
        spacePressed = true;
    }
    else
        spacePressed = false;

    // apply gravity
    velocity.y += GR;

    nextPos.move(velocity);

    desiredOffestY = nextPos.getPosition().y - rect.getPosition().y;
}

void Player::fire()
{
    auto m = new Missile(rect.getPosition(), left ? -1 : 1);
    missiles.push_back(*m);
}

void Player::render(float offset)
{
    // detect stop
    // (if we wanted to move, but we can`t)
    if ( desiredOffestY > 0 && offset == 0) {
        velocity.y = 0;
        jump = false;
    }
    else
        jump = true;

    // bugfix
    if (down && (rect.getPosition().y == 541.6 || rect.getPosition().y == 541.0))
        offset = 0;

    nextPos.setPosition(nextPos.getPosition().x, rect.getPosition().y + offset);
    rect.setPosition(nextPos.getPosition());
    rect.setSize(nextPos.getSize());
    sprite.setPosition(rect.getPosition());

}
