
#ifndef DINO_LEVEL_HPP
#define DINO_LEVEL_HPP

#include <iostream>
#include <SFML/Graphics.hpp>
#include "globals.hpp"
#include "Entity.hpp"
#include "Player.hpp"
#include "Cactus.hpp"
#include "Camera.hpp"
#include "Pterodactyl.hpp"

class Level {

public:
    Level(sf::RenderWindow * win);
    void update();

private:
    void loadFromFile();
    void initObjects();
    float checkMovement(sf::RectangleShape rect, float offset);

    sf::RenderWindow * window;
    sf::Texture platformTexture;

    Camera * camera;
    std::vector<std::vector<int>> tiles;
    std::vector<sf::Sprite> platforms;
    Player player;
    float playerOffset = 0;
    std::vector<Cactus> cactuses;
    std::vector<Pterodactyl> pteros;
    sf::RectangleShape background;

};


#endif //DINO_LEVEL_HPP
