#include <iostream>
#include <SFML/Graphics.hpp>
#include "Level.hpp"
#include "StandardMode.hpp"
#include "Menu/Menu.hpp"

int lvlTilesW, lvlTilesH;

int main(int argc, const char ** argv)
{

    sf::RenderWindow window(sf::VideoMode(WIN_W, WIN_H), "DINO REMASTERED_");
    window.setFramerateLimit(60);


    Menu menu(&window);
    Level level(&window);
    StandardMode standard(&window);


    while (window.isOpen())
    {
        if (menu.getState() == -1)
            menu.update();
        else if(menu.getState() == 0)
            standard.update();
        else
            level.update();

    }


    return 0;

}
