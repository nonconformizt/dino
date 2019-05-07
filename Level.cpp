
#include "Level.hpp"

Level::Level()
{
    loadFromFile();

    background.setPosition(0, 0);
    background.setSize(sf::Vector2f(LVL_W, LVL_H));
    background.setFillColor(sf::Color::White);

    platformTexture.loadFromFile("assets/tile.png");
    sf::Sprite tempSprite;
    tempSprite.setTexture(platformTexture);
    tempSprite.setTextureRect(sf::IntRect(0, 0, 30, 10));

    for (int i = 0; i < LVL_TILES_H; i++) {
        for (int j = 0; j < LVL_TILES_W; j++) {
            if (tiles[i][j] == 1) {
                tempSprite.setPosition(TILE_W * j, TILE_H * i);
                platforms.push_back(tempSprite);
            }
        }
    }

    sf::Vector2f pos[6] = {{170, 260}, {820, 70}, {200, 20}, {525, 20}, {550, 20}, {575, 20}};

    for (int i = 0; i < 6; i++) {
        auto c = new Cactus(pos[i]);
        cactuses.push_back(*c);
    }

    sf::Vector2f pt[2] = {{900, 230}, {600, 180}};

    for (int i = 0; i < 2; i++) {
        auto p = new Pterodactyl(pt[i], 4.0);
        pteros.push_back(*p);
    }

}

void Level::loadFromFile()
{
    FILE * mapFile = fopen("assets/level.txt", "r");
    char buffer[LVL_TILES_W + 1];

    for (int i = 0; i < LVL_TILES_H; i++) {
        fread(buffer, LVL_TILES_W, 1, mapFile);

        for (int j = 0; j < LVL_TILES_W; j++)
            tiles[i][j] = buffer[j] - '0';

        fseek(mapFile, 2, SEEK_CUR); // skip new line symbol
                                     // (dont ask me why second arg is 2)
    }

    fclose(mapFile);
}

float Level::checkMovement(sf::RectangleShape rect, float offset)
{
    // always can go up
    if (offset <= 0)
        return offset;

    rect.move(0, offset);

    sf::FloatRect tile = {0, 0, TILE_W, TILE_H};
    int leftTile_j = int(rect.getPosition().x + 25) / TILE_W, // the most left tile under player (index)
        rightTile_j = int(rect.getPosition().x + rect.getSize().x - 15) / TILE_W, // the most right one
        topRow = int(rect.getPosition().y) / TILE_H - int(offset*2) / TILE_H + 4; // the upper tilemap layer
    float limit;


    for (int j = leftTile_j; j <= rightTile_j; j++) {
        for (int i = topRow; i < topRow + 10; i++) {
            if (i >= 0 && i < LVL_TILES_H && j >= 0 && j < LVL_TILES_W) {
                if (tiles[i][j] == 1) {
                    tile.left = 30 * j;
                    tile.top = 10 * i;
                    if (rect.getGlobalBounds().intersects(tile)) {

                        rect.move(0, -offset); // revert to initial position
                        limit = tile.top - rect.getPosition().y - rect.getSize().y; // player can move down
                                                                                    // only to this point, never lower

                        if (limit < 0) limit = offset; // very strange thing

                        return (limit >= offset) ? offset : limit;
                    }
                }
            }
        }
    }

    return offset;
}
