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

#define LIVES_N 3

class Level {

public:
    explicit Level(sf::RenderWindow * win);
    void update();
    void load(size_t lvl);

private:
    void getLevelFromFile();
    void initObjects();
    void createEntities();
    void drawScore();
    void kill();
    float checkMovement(sf::RectangleShape rect, float offset);

    size_t currentLevel = 1;

    sf::RenderWindow * window;
    sf::RectangleShape background;
    sf::Texture platformTexture;

    Camera * camera;

    std::vector<std::vector<int>> tiles;
    std::vector<sf::Sprite> platforms;

    Player player;
    sf::Vector2f startPosition;
    float playerOffset = 0;
    sf::Vector2f saving = sf::Vector2f(50, 1300);
    bool dead = false;

    int lives = LIVES_N;
    sf::Texture heart;
    sf::Sprite hearts[LIVES_N];

    std::vector<sf::Vector2f> cactPos;
    std::vector<Cactus> cactuses;

    std::vector<sf::Vector2f> pteroPos;
    std::vector<float> pteroSpeed;
    std::vector<Pterodactyl> pteros;

    std::vector<sf::Vector2f> coinPos;
    std::vector<Coin> coins;
    int coinsCollected = 0;

    sf::Vector2f flagPosition;
    sf::Texture flagTexture;
    sf::Sprite flag;

    sf::Font font;
    sf::Text score, scoreShadow;
    sf::Texture gameOverTexture;
    sf::Sprite gameOver;
    sf::Text gameOverText, gameoverSmallText;

};


#endif //DINO_LEVEL_HPP
