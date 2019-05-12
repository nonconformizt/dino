
#ifndef DINO_LEVEL_HPP
#define DINO_LEVEL_HPP

#include <iostream>
#include <SFML/Graphics.hpp>
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
    int tiles[LVL_TILES_H][LVL_TILES_W] = {{0}};
    std::vector<sf::Sprite> platforms;
    Player player;
    float playerOffset;
    std::vector<Cactus> cactuses;
    std::vector<Pterodactyl> pteros;
    sf::RectangleShape background;

};


#endif //DINO_LEVEL_HPP
