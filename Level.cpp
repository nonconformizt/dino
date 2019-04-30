
#include "Level.hpp"

Level::Level()
{
    loadFromFile();
    sf::RectangleShape tempRect;
    for (int i = 0; i < 60; i++) {
        for (int j = 0; j < 33; j++) {
            if (tiles[i][j] == 1) {
                tempRect.setPosition(30*j, 10*i);
                tempRect.setSize(sf::Vector2f(30, 10));
                tempRect.setFillColor(sf::Color::Black);
                platforms.push_back(tempRect);
            }
        }
    }
}

void Level::loadFromFile()
{
    FILE * mapFile = fopen("assets/level.txt", "r");
    char buffer[33 + 1];

    for (int i = 0; i < 60; i++) {
        fread(buffer, 33, 1, mapFile);
        for (int j = 0; j < 33; j++) {
            tiles[i][j] = buffer[j] - '0';
            std::cout << buffer[j] - '0';
        }
        std::cout << "\n";
    }
}




