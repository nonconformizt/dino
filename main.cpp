#include <iostream>
#include <SFML/Graphics.hpp>
#include "Player.hpp"

int main(int argc, const char ** argv) {

    class Player player;


    sf::RenderWindow window(sf::VideoMode(800, 600), "Dino");
    window.setFramerateLimit(60);

    while (window.isOpen())
    {
        // Process events
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
            if ((event.type == sf::Event::KeyPressed) && (event.key.code == sf::Keyboard::Escape))
                window.close();
        }

        window.clear();
        player.update();

        /* TEMP BACKGROUND */
        sf::RectangleShape r;
        r.setPosition(0, 0);
        r.setSize(sf::Vector2f(800, 600));
        r.setFillColor(sf::Color(255, 255, 255, 255));
        window.draw(r);

        window.draw(player.sprite);
        window.display();
    }


    return 0;
}