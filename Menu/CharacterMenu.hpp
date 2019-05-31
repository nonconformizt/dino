
#ifndef DINO_CHARACTERMENU_HPP
#define DINO_CHARACTERMENU_HPP

#include "Modal.hpp"

class CharacterMenu : public Modal {

public:
    CharacterMenu(sf::RenderWindow * win, sf::Font * f);
    void render() final;

private:
    sf::RectangleShape block;


};


#endif //DINO_CHARACTERMENU_HPP
