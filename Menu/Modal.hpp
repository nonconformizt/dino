
#ifndef DINO_MODAL_HPP
#define DINO_MODAL_HPP

#include <SFML/Graphics.hpp>
#include "../config.h"

class Modal {

public:
    void show() { shown = true; }

    virtual void hide() { shown = false; }
    bool isShown() { return shown; }
    virtual void render() = 0;

protected:
    bool shown = false;

    sf::RenderWindow * window;
    sf::Texture blockTex;
    sf::Sprite block;
    sf::RectangleShape bg;
    sf::Text title;
    sf::Font * font;

};


#endif //DINO_MODAL_HPP
