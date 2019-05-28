#include <iostream>
#include "globals.hpp"
#include <SFML/Graphics.hpp>
#include "Level.hpp"
#include "StandardMode.hpp"
#include "Menu/Menu.hpp"

int lvlTilesW, lvlTilesH;

int main(int argc, const char ** argv)
{

    sf::RenderWindow window(sf::VideoMode(WIN_W, WIN_H), "DINO REMASTERED_");
    window.setFramerateLimit(60);

    size_t state = -1;


    Menu menu(&window);
    Level level(&window);
    StandardMode standard(&window);


    while (window.isOpen())
    {
        if (state == -1) // menu is opened
        {
            state = menu.getState();

            if (state == 0)
                standard.reset();
            else if (state >= 1 && state <= 3) {
                level.load(state);
            }
        }

        if (state == -1)
            menu.update();
        else if(state == 0)
            standard.update();
        else
            level.update();

    }


    return 0;

}


