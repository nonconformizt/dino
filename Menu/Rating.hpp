
#ifndef DINO_RATING_HPP
#define DINO_RATING_HPP

#include "Modal.hpp"

#define SP_N 60

class Rating : public Modal {

public:
    explicit Rating(sf::RenderWindow * win, sf::Font * f);
    void render() final;


private:
    void initSparks();
    void updateSparks();

    sf::Text listText[10],
             listNum[10];
    sf::RectangleShape listBullet[10];
    sf::RectangleShape sparks[SP_N];
};


#endif //DINO_RATING_HPP
