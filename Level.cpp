
#include "Level.hpp"

Level::Level(sf::RenderWindow * win)
{
    window = win;
    getLevelFromFile();
    initObjects();

    camera = new Camera(window, &(player.rect));

}

void Level::getLevelFromFile()
{
    std::string filename = "assets/level"+ std::to_string(currentLevel) +".txt";
    FILE * mapFile = fopen(filename.c_str(), "r");

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

        coinPos.emplace_back(sf::Vector2f(tempX, LVL_H - tempY));
    }

    // read player start position
    fscanf(mapFile, "%d", &tempX);
    fscanf(mapFile, "%d", &tempY);

    startPosition = saving = sf::Vector2f(tempX, LVL_H - tempY);

    // read flag position
    fscanf(mapFile, "%d", &tempX);
    fscanf(mapFile, "%d", &tempY);

    flagPosition = sf::Vector2f(tempX, LVL_H - 55 - tempY); // 55 is flag height

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
            window->close(); // open menu here
        else if (event.type == sf::Event::KeyReleased && event.key.code == sf::Keyboard::Q)
            saving = player.rect.getPosition();
        else if (player.dead && event.type == sf::Event::KeyReleased && event.key.code == sf::Keyboard::Enter)
            // reload game
            load(currentLevel);
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

    window->draw(flag);

    if (!player.dead)
    {
        player.update();
        playerOffset = checkMovement(player.rect, player.desiredOffsetY);
        player.render(playerOffset);
    }
    window->draw(player.sprite);

    int posX = int( player.rect.getPosition().x);
    int posY = int( LVL_H - (player.rect.getPosition().y + player.rect.getSize().y) );
    std::cout << "x: " << posX << "; y: " << posY << std::endl;

    drawScore();

    if (player.dead)
        drawGameOver();


    for (const auto & h : hearts)
        window->draw(h);

    // check if player must die

    for( auto & cactus: cactuses )
        if (cactus.collision(player.sprite.getGlobalBounds())) {
            kill();
            break;
        }

    for( auto & ptero: pteros )
        if (!ptero.dead && ptero.collision(player.sprite.getGlobalBounds())) {
            kill();
            break;
        }

    // check if pterodactyl must die

    for( auto & missile : player.missiles )
        for( auto & ptero: pteros )
            if (!ptero.dead)
                if (ptero.collision(missile.sprite.getGlobalBounds()))
                    ptero.dead = true;

    // check if coin collected

    for (auto coinIter = coins.begin(); coinIter != coins.end(); coinIter++)
    {
        if (player.rect.getGlobalBounds().intersects(coinIter->sprite.getGlobalBounds()))
        {
            delete(&coinIter);
            coins.erase(coinIter);
            coinsCollected++;
            coinIter--;
        }
    }

    // check if flag was reached
    if (player.rect.getGlobalBounds().intersects(flag.getGlobalBounds()))
        window->close();

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
    score.setString("COINS: 0");
    score.setPosition(0, lvlTilesH * 10 - 100);
    score.setPosition(WIN_W - score.getGlobalBounds().width - 20, 20);
    score.setFillColor(GRAY);

    scoreShadow.setFont(font);
    scoreShadow.setCharacterSize(20);
    scoreShadow.setString("COINS: 0");
    scoreShadow.setPosition(0 + 3, lvlTilesH * 10 - 100 + 3);
    scoreShadow.setPosition(WIN_W - score.getGlobalBounds().width - 20, 20);
    scoreShadow.setFillColor(sf::Color::White);

    gameOverTexture.loadFromFile("assets/gameover.png");
    gameOver.setTexture(gameOverTexture);
    gameOver.setPosition(WIN_W / 2 - (float) gameOverTexture.getSize().x / 2, 120);

    gameOverText.setFont(font);
    gameOverText.setString("GAME OVER");
    gameOverText.setCharacterSize(45);
    gameOverText.setFillColor(GRAY);
    gameOverText.setPosition(WIN_W / 2 - (gameOverText.getGlobalBounds().width / 2), 200);

    gameoverSmallText.setFont(font);
    gameoverSmallText.setCharacterSize(20);
    gameoverSmallText.setString("Press Esc to open menu\n or Enter to try again");
    gameoverSmallText.setFillColor(GRAY);
    gameoverSmallText.setPosition(WIN_W / 2 - (gameoverSmallText.getGlobalBounds().width / 2), 280);


    heart.loadFromFile("assets/heart.png");
    for (int i = LIVES_N - 1; i >= 0; i--)
    {
        hearts[i].setTextureRect(sf::IntRect(0, 0, 22, 20));
        hearts[i].setTexture(heart);
        hearts[i].setPosition(WIN_W - 40 - i * 30, 50);
    }

    platformTexture.loadFromFile("assets/tile.png");

    flagTexture.loadFromFile("assets/flag.png");
    flag.setTexture(flagTexture);
    flag.setTextureRect(sf::IntRect(0, 0, 30, 55));
    flag.setPosition(flagPosition);

    player.teleport(startPosition);
}

void Level::createEntities()
{
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

void Level::drawGameOver()
{
    window->setView(window->getDefaultView());
    window->draw(gameOver);
    window->draw(gameOverText);
    window->draw(gameoverSmallText);
}

void Level::drawHearts()
{
    for (int i = 0; i < LIVES_N; i++)
    {
        if (lives > i)
            hearts[i].setTextureRect(sf::IntRect(0, 0, 22, 20));
        else
            hearts[i].setTextureRect(sf::IntRect(22, 0, 22, 20));
    }
}

void Level::kill()
{
    lives--;
    if (lives <= 0)
    {
        player.dead = true;
        return;
    }

    drawHearts();

    // load saving
    player.teleport(saving);

    window->clear(GRAY);
    window->display();
    sf::sleep(sf::seconds(0.7));
}

// almost constructor
void Level::load(const size_t lvl)
{
    currentLevel = lvl;

    cactuses.clear();

    pteros.clear();
    pteroSpeed.clear();
    pteroPos.clear();

    coins.clear();
    coinPos.clear();
    coinsCollected = 0;

    tiles.clear();
    platforms.clear();

    lives = LIVES_N;
    playerOffset = 0;
    player.dead = false;
    player.teleport(sf::Vector2f(100, 800));
    drawHearts();

    score.setString("COINS: 0");
    scoreShadow.setString("COINS: 0");

    getLevelFromFile();
    createEntities();

    background.setSize(sf::Vector2f(LVL_W, LVL_H));
}

