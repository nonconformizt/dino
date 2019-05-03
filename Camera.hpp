
#ifndef DINO_CAMERA_HPP
#define DINO_CAMERA_HPP

#include "config.h"
#include <iostream>
#include <SFML/Graphics.hpp>

class Camera {

public:
    Camera(sf::RenderWindow * win, sf::RectangleShape * rect);
    void update();

private:
    sf::View view;
    sf::RenderWindow * window;
    sf::RectangleShape * player;

};


#endif //DINO_CAMERA_HPP
