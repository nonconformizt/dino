
#ifndef DINO_RATING_HPP
#define DINO_RATING_HPP

#include <SFML/Graphics.hpp>
#include "../config.h"
#include "Modal.hpp"

class Rating : public Modal {

public:
    explicit Rating(sf::RenderWindow * win, sf::Font * f);
    void render() final;


private:
    sf::Text listText[10],
             listNum[10];
    sf::RectangleShape listBullet[10];
};


#endif //DINO_RATING_HPP
