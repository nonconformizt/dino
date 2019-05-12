#include <iostream>
#include <SFML/Graphics.hpp>
#include "Level.hpp"
#include "StandardMode.hpp"
#include "Player.hpp"
#include "Missile.hpp"
#include "Camera.hpp"
#include "Cactus.hpp"
#include "Menu/Menu.hpp"

int main(int argc, const char ** argv)
{

    sf::RenderWindow window(sf::VideoMode(WIN_W, WIN_H), "Dino");
    window.setFramerateLimit(60);


    Menu menu(&window);
    Level level(&window);
    StandardMode standart(&window);


    while (window.isOpen())
    {
        if (menu.getState() == -1)
            menu.update();
        else if(menu.getState() == 0)
            standart.update();
        else
            level.update();

    }


    return 0;

}
