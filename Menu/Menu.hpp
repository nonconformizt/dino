
#ifndef DINO_MENU_HPP
#define DINO_MENU_HPP

#include "../config.h"
#include <SFML/Graphics.hpp>
#include <iostream>

class Menu {

private:
    Menu();
    int getState(); // returns number of level, if user intends to run some,
                    // or 0 if user intends to run "standard mode"
                    // or -1 if we`r still showing menu

public:

    sf::RenderWindow window;
    int state; // see getState();

    sf::Text title,
             subtitle,
             btn1Label,
             btn2Label;
    sf::Sprite btn1,
               btn2,
               smallBtns[3];

};


#endif //DINO_MENU_HPP
