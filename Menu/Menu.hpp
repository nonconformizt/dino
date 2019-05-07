
#ifndef DINO_MENU_HPP
#define DINO_MENU_HPP

#include "../config.h"
#include <SFML/Graphics.hpp>
#include <iostream>

class Menu {

public:
    Menu(sf::RenderWindow * win);
    int getState(); // returns number of level, if user intends to run some,
                    // or 0 if user intends to run "standard mode"
                    // or -1 if we`r still showing menu
    void update();

private:

    sf::RenderWindow * window;
    int state = -1; // see getState();

    sf::Font font;
    const sf::Color gray = sf::Color(83, 83, 83);
    sf::Text title,
             subtitle,
             btn1Label,
             btn2Label;
    sf::Sprite btn1,
               btn2,
               smallBtns[3];
    sf::RectangleShape sparks[40],
                       background;

};


#endif //DINO_MENU_HPP
