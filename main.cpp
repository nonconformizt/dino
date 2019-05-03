#include <iostream>
#include <SFML/Graphics.hpp>
#include "Level.hpp"
#include "Player.hpp"
#include "Missile.hpp"
#include "Camera.hpp"

int main(int argc, const char ** argv)
{

    sf::RenderWindow window(sf::VideoMode(WIN_W, WIN_H), "Dino");
    window.setFramerateLimit(60);

    class Level level;
    class Player player;
    float playerOffset;
    class Camera camera(&window, &(player.rect));


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

        window.draw(level.background);

        for( auto const& platform: level.platforms )
            window.draw(platform);

        for( auto const& missile : player.missiles )
            window.draw(missile.sprite);

        playerOffset = level.checkMovement(player.rect, player.desiredOffestY);
        player.render(playerOffset);
        window.draw(player.sprite);

        camera.update();

        window.display();
    }

    return 0;
}
