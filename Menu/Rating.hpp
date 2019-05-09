
#ifndef DINO_RATING_HPP
#define DINO_RATING_HPP

#include <SFML/Graphics.hpp>


class Rating {

public:
    Rating(sf::RenderWindow * win);
    void show() { shown = true; }
    void hide() { shown = false; }
    void render();


private:
    bool shown = false;

    sf::RenderWindow * window;
    sf::Texture blockTex;
    sf::Sprite block;

};


#endif //DINO_RATING_HPP
