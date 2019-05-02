#include <iostream>
#include <SFML/Graphics.hpp>
#include "Level.hpp"
#include "Player.hpp"
#include "Missile.hpp"

int main(int argc, const char ** argv) {

    class Level level;
    class Player player;
    float playerOffset;

    sf::RenderWindow window(sf::VideoMode(990, 600), "Dino");
    window.setFramerateLimit(60);

    while (window.isOpen())
    {
        // Process events
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed || event.key.code == sf::Keyboard::Escape)
                window.close();
        }

        window.clear();
        player.update();

        for( auto & missile : player.missiles )
            missile.update();

        /* TEMP BACKGROUND */
        /* SOON WILL BE REPLACED WITH MAP */
        sf::RectangleShape r;
        r.setPosition(0, 0);
        r.setSize(sf::Vector2f(990, 600));
        r.setFillColor(sf::Color(255, 255, 255, 255));
        window.draw(r);

        for( auto const& platform: level.platforms )
            window.draw(platform);

        for( auto const& missile : player.missiles )
            window.draw(missile.sprite);

        playerOffset = level.checkMovement(player.rect, player.desiredOffestY);
        player.render(playerOffset);
        window.draw(player.sprite);

        window.display();
    }


    return 0;
}
