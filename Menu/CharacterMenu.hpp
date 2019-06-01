
#ifndef DINO_CHARACTERMENU_HPP
#define DINO_CHARACTERMENU_HPP

#include "Modal.hpp"

class CharacterMenu : public Modal {

public:
    CharacterMenu(sf::RenderWindow * win, sf::Font * f);
    void render() final;
    int mouseClicked(sf::Vector2i pos);
    int getCharacter() { return activeCharacter; }

    void navForward()
        { activeCharacter++; if (activeCharacter > 2) activeCharacter = 0; };
    void navBack()
        { activeCharacter--; if (activeCharacter < 0) activeCharacter = 2; };

private:
    sf::RectangleShape block;
    sf::Texture characterListTex;
    sf::Sprite characterListBoxes[3];

    sf::Texture charactersTex[3];
    sf::Sprite characters[3];

    int activeCharacter = -1; // numeration from zero;

    int prevMouseX = 0, prevMouseY = 0;

};


#endif //DINO_CHARACTERMENU_HPP
