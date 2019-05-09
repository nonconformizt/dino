
#ifndef DINO_RATING_HPP
#define DINO_RATING_HPP

#include <SFML/Graphics.hpp>
#include "../config.h"

class Rating {

public:
    explicit Rating(sf::RenderWindow * win, sf::Font * f);
    void show() { shown = true; }
    void hide() { shown = false; }
    bool isShown() { return shown; }
    void render();


private:
    bool shown = false;

    sf::RenderWindow * window;
    sf::Texture blockTex;
    sf::Sprite block;
    sf::RectangleShape bg;
    sf::Text title;
    sf::Font * font;

    sf::Text listText[10],
             listNum[10];
    sf::RectangleShape listBullet[10];
};


#endif //DINO_RATING_HPP
