

#ifndef DINO_LEVELMENU_HPP
#define DINO_LEVELMENU_HPP

#include "Modal.hpp"


class LevelMenu : public Modal {

public:
    LevelMenu(sf::RenderWindow * win, sf::Font * f);
    void render() final;

private:
    sf::RectangleShape block;

    sf::Texture levelListTex;
    sf::Sprite levelListBoxes[10];

};


#endif //DINO_LEVELMENU_HPP
