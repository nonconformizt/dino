
#include "Level.hpp"

Level::Level(sf::RenderWindow * win)
{
    window = win;
    loadFromFile();
    initObjects();

    camera = new Camera(window, &(player.rect));

}

void Level::loadFromFile()
{
    FILE * mapFile = fopen("assets/level.txt", "r");
    char ch;
    int i = 0, j = 0;

    while ((ch = fgetc(mapFile)) != '=') // '=' is a sign of map end
    {
        auto r = new std::vector<int>;

        do {
            r->push_back(ch - '0');
            j++;
        } while ((ch = fgetc(mapFile)) != '\n' && ch != EOF);

        tiles.push_back(*r);
        lvlTilesW = j;
        i++;
        j = 0;
    }
    lvlTilesH = i;

    int tempX, tempY;
    while (true)
    {
        fscanf(mapFile, "%d", &tempX);
        if (tempX == -1) // -1 is a sign of pterodactyl array end
            break;

        fscanf(mapFile, "%d", &tempY);
        if (tempY == -1)
            break;

        pteroPos.emplace_back(sf::Vector2f(tempX, tempY));
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
            if (i >= 0 && i < lvlTilesH && j >= 0 && j < lvlTilesW) {
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

void Level::update()
{
    // Process events
    sf::Event event = sf::Event();
    while (window->pollEvent(event))
    {
        if (event.type == sf::Event::Closed || event.key.code == sf::Keyboard::Escape)
            window->close();
    }

    window->clear();

    window->draw(background);

    for( auto const& platform: platforms )
        window->draw(platform);

    for( auto const& cactus: cactuses )
        window->draw(cactus.sprite);

    for( auto & ptero: pteros ) {
        ptero.update();
        window->draw(ptero.sprite);
    }

    for( auto & coin: coins ) {
        coin.update();
        window->draw(coin.sprite);
    }

    for( auto & missile : player.missiles ) {
        missile.update();
        window->draw(missile.sprite);
    }

    player.update();
    playerOffset = checkMovement(player.rect, player.desiredOffestY);
    player.render(playerOffset);
    window->draw(player.sprite);

    camera->update();


    // check if player must die

    for( auto & cactus: cactuses )
        if (cactus.collision(player.sprite.getGlobalBounds()))
            window->close();

    for( auto & ptero: pteros )
        if (!ptero.dead && ptero.collision(player.sprite.getGlobalBounds()))
            window->close();

    // check if pterodactyl must die

    for( auto & missile : player.missiles )
        for( auto & ptero: pteros )
            if (!ptero.dead)
                if (ptero.collision(missile.sprite.getGlobalBounds()))
                    ptero.dead = true;

    // check if coin collected

    for (auto it = coins.begin(); it != coins.end(); it++) {
        if (player.rect.getGlobalBounds().intersects(it->sprite.getGlobalBounds())) {
            coins.erase(it);
            it --;
        }
    }

    window->display();
}

void Level::initObjects()
{
    background.setPosition(0, 0);
    background.setSize(sf::Vector2f(LVL_W, LVL_H));
    background.setFillColor(sf::Color::White);

    platformTexture.loadFromFile("assets/tile.png");
    sf::Sprite tempSprite;
    tempSprite.setTexture(platformTexture);
    tempSprite.setTextureRect(sf::IntRect(0, 0, 30, 10));

    for (int i = 0; i < lvlTilesH; i++) {
        for (int j = 0; j < lvlTilesW; j++) {
            if (tiles[i][j] == 1) {
                tempSprite.setPosition(TILE_W * j, TILE_H * i);
                platforms.push_back(tempSprite);
            }
        }
    }

    sf::Vector2f cact[6] = {{170, 260}, {820, 70}, {200, 20}, {525, 20}, {550, 20}, {575, 20}};

    for (auto cPos : cact) {
        auto c = new Cactus(cPos);
        cactuses.push_back(*c);
    }

    for (const auto pos: pteroPos) {
        auto p = new Pterodactyl(pos, 4.0);
        pteros.push_back(*p);
    }

    sf::Vector2f coinsP[3] = {{200, 200}, {300, 200}, {400, 200}};

    for (auto coinPosition : coinsP) {
        auto c = new Coin(coinPosition);
        coins.push_back(*c);
    }

}
