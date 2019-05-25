
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

    int tempX, tempY, tempSpeed;

    // read pterodactyls position
    while (true)
    {
        fscanf(mapFile, "%d", &tempX);
        if (tempX == -1) // -1 is a sign of pterodactyl array end
            break;
        fscanf(mapFile, "%d", &tempY);
        if (tempY == -1)
            break;
        fscanf(mapFile, "%d", &tempSpeed);
        if (tempSpeed == -1)
            break;

        pteroPos.emplace_back(sf::Vector2f(tempX, lvlTilesH * TILE_H - tempY));
        pteroSpeed.push_back(tempSpeed);
    }

    // read cactuses position
    while (true)
    {
        fscanf(mapFile, "%d", &tempX);
        if (tempX == -1)
            break;
        fscanf(mapFile, "%d", &tempY);
        if (tempY == -1)
            break;

        cactPos.emplace_back(sf::Vector2f(tempX, tempY));
    }

    // read coins position
    while (true)
    {
        fscanf(mapFile, "%d", &tempX);
        if (tempX == -1)
            break;
        fscanf(mapFile, "%d", &tempY);
        if (tempY == -1)
            break;

        coinPos.emplace_back(sf::Vector2f(tempX, lvlTilesH * TILE_H - tempY));
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

    camera->update();

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
    playerOffset = checkMovement(player.rect, player.desiredOffsetY);
    player.render(playerOffset);
    window->draw(player.sprite);

    //int posX = int( player.rect.getPosition().x);
    //int posY = int( lvlTilesH * TILE_H - (player.rect.getPosition().y + player.rect.getSize().y) );
    //std::cout << "x: " << posX << "; y: " << posY << std::endl;

    drawScore();

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
            coins.erase(it--);
            coinsCollected++;
        }
    }

    window->display();
}

void Level::initObjects()
{
    background.setPosition(0, 0);
    background.setSize(sf::Vector2f(LVL_W, LVL_H));
    background.setFillColor(sf::Color::White);

    font.loadFromFile("assets/font.ttf");
    score.setFont(font);
    score.setCharacterSize(20);
    score.setString("Hello world");
    score.setPosition(0, lvlTilesH * 10 - 100);
    score.setPosition(WIN_W - score.getGlobalBounds().width - 20, 20);
    score.setFillColor(GRAY);

    scoreShadow.setFont(font);
    scoreShadow.setCharacterSize(20);
    scoreShadow.setString("Hello world");
    scoreShadow.setPosition(0 + 3, lvlTilesH * 10 - 100 + 3);
    scoreShadow.setPosition(WIN_W - score.getGlobalBounds().width - 20, 20);
    scoreShadow.setFillColor(sf::Color::White);

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

    for (auto cPos : cactPos) {
        auto c = new Cactus(cPos);
        cactuses.push_back(*c);
    }

    for (int i = 0; i < pteroPos.size(); i++) {
        auto p = new Pterodactyl(pteroPos[i], pteroSpeed[i]);
        pteros.push_back(*p);
    }

    for (auto coinPosition : coinPos) {
        auto c = new Coin(coinPosition);
        coins.push_back(*c);
    }

}

void Level::drawScore()
{
    window->setView(window->getDefaultView());
    score.setString("COINS: " + std::to_string(coinsCollected));
    score.setPosition(WIN_W - score.getGlobalBounds().width - 20, 20);
    window->draw(score);
}
