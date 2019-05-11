

#ifndef DINO_LEVELMENU_HPP
#define DINO_LEVELMENU_HPP

#include "Modal.hpp"

// number of levels
#define LVLS_N 5
#define SPARKS 100


class LevelMenu : public Modal {

public:
    LevelMenu(sf::RenderWindow * win, sf::Font * f);
    void render() final;
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
    sf::Sprite levelListBoxes[10];
    sf::Text levelListNums[10];
    sf::Sprite levelStars[10][3];
    sf::Texture levelStarTex, levelSmallStarTex;
    sf::RectangleShape sparks[SPARKS];

    int activeLevel = 0;
    int levelInfo[10] = {3, 0, 2, 1, 0}; // how many stars gamer have in each level

};


#endif //DINO_LEVELMENU_HPP
