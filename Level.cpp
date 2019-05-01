
#include "Level.hpp"

Level::Level()
{
    loadFromFile();
    platformTexture.loadFromFile("assets/tile.png");
    sf::Sprite tempSprite;
    tempSprite.setTexture(platformTexture);
    tempSprite.setTextureRect(sf::IntRect(0, 0, 30, 10));

    for (int i = 0; i < 60; i++) {
        for (int j = 0; j < 33; j++) {
            if (tiles[i][j] == 1) {
                tempSprite.setPosition(30*j, 10*i);
                platforms.push_back(tempSprite);
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

        for (int j = 0; j < 33; j++)
            tiles[i][j] = buffer[j] - '0';

        fseek(mapFile, 2, SEEK_CUR); // skip new line symbol
                                     // (dont ask me why second arg is 2)
    }

    fclose(mapFile);
}

float Level::checkMovement(sf::RectangleShape rect, float offset)
{
    using namespace std;

    // always can go up
    if (offset <= G)
        return offset;

    rect.move(0, offset);

    sf::FloatRect tile = {0, 0, 30, 10};
    int leftTile_j = int(rect.getPosition().x) / 30, // the most left tile under player (index)
        rightTile_j = int(rect.getPosition().x + rect.getSize().x) / 30, // the most right one
        topRow = int(rect.getPosition().y) / 10 + 6; // the upper tilemap layer
    float limit;


    for (int j = leftTile_j; j <= rightTile_j; j++) {
        for (int i = topRow; i < topRow + 10; i++) {
            if (i >= 0 && i < 60 && j >= 0 && j < 33) {
                if (tiles[i][j] == 1) {
                    tile.left = 30 * j;
                    tile.top = 10 * i;
                    if (rect.getGlobalBounds().intersects(tile)) {

                        rect.move(0, -offset); // revert to initial position
                        limit = tile.top - rect.getPosition().y - rect.getSize().y; // player can move down
                                                                                    // only to this point, never lower
                        return (limit >= offset) ? offset : limit;

                    }
                }
            }
        }
    }

//  cout << offset << endl;
    return offset;

}


