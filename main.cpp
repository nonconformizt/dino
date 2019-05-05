#include <iostream>
#include <windows.h>
#include <SFML/Graphics.hpp>
#include "Level.hpp"
#include "Player.hpp"
#include "Missile.hpp"
#include "Camera.hpp"
#include "Cactus.hpp"

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

        window.draw(level.background);

        for( auto const& platform: level.platforms )
            window.draw(platform);

        for( auto const& cactus: level.cactuses )
            window.draw(cactus.sprite);

        for( auto & ptero: level.pteros ) {
            ptero.update();
            window.draw(ptero.sprite);
        }

        for( auto & missile : player.missiles ) {
            missile.update();
            window.draw(missile.sprite);
        }

        player.update();
        playerOffset = level.checkMovement(player.rect, player.desiredOffestY);
        player.render(playerOffset);
        window.draw(player.sprite);

        camera.update();

        // check if player must die

        for( auto & cactus: level.cactuses )
            if (cactus.collision(player.sprite.getGlobalBounds()))
                window.close();

        for( auto & ptero: level.pteros )
            if (ptero.collision(player.sprite.getGlobalBounds()))
                window.close();


        window.display();
    }

    MessageBoxA(nullptr, "GAME OVER!", "Dino", 0);

    return 0;

}
