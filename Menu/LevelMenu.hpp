

#ifndef DINO_LEVELMENU_HPP
#define DINO_LEVELMENU_HPP

#include "Modal.hpp"

// number of levels
#define LVLS_N 3
#define MAX_LVLS 10
#define SPARKS 100


class LevelMenu : public Modal {

public:
    LevelMenu(sf::RenderWindow * win, sf::Font * f);
    void render() final;
    int mouseClicked(sf::Vector2i pos);
    void navForward()
                { activeLevel++; if (activeLevel > LVLS_N) activeLevel = 1; };
    void navBack()
                { activeLevel--; if (activeLevel <= 0) activeLevel = LVLS_N; };
    int getLevel() { return activeLevel; }

private:
    void redrawStars();
    void initSparks();
    void updateSparks();

    sf::RectangleShape block;
    sf::Texture levelListTex;
    sf::Sprite levelListBoxes[MAX_LVLS];
    sf::Text levelListNums[MAX_LVLS];
    sf::Sprite levelStars[MAX_LVLS][3];
    sf::Texture levelStarTex, levelSmallStarTex;
    sf::RectangleShape sparks[SPARKS];

    int activeLevel = 0;
    int levelCollectedStars[MAX_LVLS] = {2, 3, 1}; // how many stars gamer have in each level

    int prevMouseX = 0, prevMouseY = 0;

};


#endif //DINO_LEVELMENU_HPP
