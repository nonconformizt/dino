#ifndef DINO_LEVEL_HPP
#define DINO_LEVEL_HPP

#include <iostream>
#include <SFML/Graphics.hpp>
#include "globals.hpp"
#include "Entity.hpp"
#include "Player.hpp"
#include "Cactus.hpp"
#include "Coin.hpp"
#include "Camera.hpp"
#include "Pterodactyl.hpp"

class Level {

public:
    explicit Level(sf::RenderWindow * win);
    void update();

private:
    void loadFromFile();
    void initObjects();
    void drawScore();
    float checkMovement(sf::RectangleShape rect, float offset);

    sf::RenderWindow * window;
    sf::RectangleShape background;
    sf::Texture platformTexture;

    Camera * camera;

    std::vector<std::vector<int>> tiles;
    std::vector<sf::Sprite> platforms;

    Player player;
    float playerOffset = 0;
    int lives;

    std::vector<sf::Vector2f> cactPos;
    std::vector<Cactus> cactuses;

    std::vector<sf::Vector2f> pteroPos;
    std::vector<float> pteroSpeed;
    std::vector<Pterodactyl> pteros;

    std::vector<sf::Vector2f> coinPos;
    std::vector<Coin> coins;
    int coinsCollected = 0;

    sf::Font font;
    sf::Text score, scoreShadow;

};


#endif //DINO_LEVEL_HPP
