
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

sf::RectangleShape Level::checkMovement(sf::RectangleShape next, sf::RectangleShape curr)
{

    sf::FloatRect tempTile;
    tempTile.width = 30;
    tempTile.height = 10;
    sf::RectangleShape tempPlayer;
    tempPlayer.setPosition(curr.getPosition());
    tempPlayer.setSize(curr.getSize());

    //std::cout << curr.getPosition().x << "; " << curr.getPosition().y << std::endl;

    int centerTileX = int(curr.getPosition().x + curr.getSize().x / 2) / 30,
        centerTileY = int(curr.getPosition().y + curr.getSize().y / 2) / 10;

    // loop through all closest to player tiles
    for (int i = centerTileX - 2; i <= centerTileX + 3; i++) {
        for (int j = centerTileY - 10; j <= centerTileY + 5; j++) {
            if (i >= 0 && j >= 0 && i < 33 && j < 60) {
                if (tiles[j][i] == 1) {
                    tempTile.left = 30 * i;
                    tempTile.top = 10 * j;
                    // if not intersects now, then MUST NOT intersect on the next frame
                    if (!curr.getGlobalBounds().intersects(tempTile)) {
                        // !kostyl begins!
                        tempPlayer.setPosition(curr.getPosition().x, next.getPosition().y);
                        if (tempPlayer.getGlobalBounds().intersects(tempTile)) {
                            std::cout << "Cant go down!\n";
                            // Cant go down!
                            next.setPosition(next.getPosition().x, curr.getPosition().y); // move out
                            return next;
                        }
                    }
                }
            }
        }
    }


    std::cout << "==== !!! Can go down !!! ====\n";
    return next;
}


