
#ifndef DINO_MENU_HPP
#define DINO_MENU_HPP

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include "../config.h"
#include "Rating.hpp"
#include "LevelMenu.hpp"
#include "CharacterMenu.hpp"
#include "TextField.hpp"

#define SPARKS_N 30

class Menu {

public:
    explicit Menu(sf::RenderWindow * win);
    size_t getState(); // returns number of level, if user intends to run some,
                       // or 0 if user intends to run "standard mode"
                       // or -1 if we`r still showing menu
    int getCharacter() { return character; }
    void open() { state = -1; };
    void update();
    void writeHighscore(int score);

private:
    void deactivateAll();
    void initSparks();
    void updateSparks();
    void pushHighscore();

    sf::RenderWindow * window;
    int state = -1; // see getState();

    int character = -1;

    sf::Font font;
    sf::Text title,
             subtitle,
             btn1Label,
             btn2Label;
    sf::Sprite btn1,
               btn2,
               smallBtns[3];
    sf::Texture smallBtnTexture[3];
    sf::Texture btnTexture;
    sf::RectangleShape sparks[SPARKS_N],
                       background;
    int activeBtn = -1;
    bool activeChanged = false;

    LevelMenu * levelMenu;
    CharacterMenu * characterMenu;
    Rating * rating;
    TextField * textField;

    sf::SoundBuffer navigateSoundBuf;
    sf::Sound navigateSound;

    int tempHigscore = 0;
    std::string tempPlayerName;

    int prevMouseX = 0, prevMouseY = 0;

};


#endif //DINO_MENU_HPP
