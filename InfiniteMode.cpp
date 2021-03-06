
#include "InfiniteMode.hpp"

InfiniteMode::InfiniteMode(sf::RenderWindow * win)
{
    window = win;
    initObjects();

    view.setCenter( (float) window->getSize().x / 2, (float) window->getSize().y / 2);
    view.setSize(window->getSize().x, window->getSize().y);
    window->setView(view);

    player.setInfiniteMode(true);

    mt.seed(time(nullptr) * sf::Mouse::getPosition().x);
}


float InfiniteMode::checkMovement(const sf::RectangleShape * rect, float offset)
{
    // always can go up
    if (offset <= 0)
        return offset;

    float bottom = rect->getPosition().y + rect->getSize().y;

    if (bottom + offset > GROUND)
        return GROUND - bottom;

    return offset;
}

void InfiniteMode::update()
{
    sf::Event event;
    while (window->pollEvent(event))
    {
        if (event.type == sf::Event::Closed || event.key.code == sf::Keyboard::Escape)
            window->close();
    }

    window->clear();
    window->setView(view);

    background.move(velocity, 0);
    window->draw(background);

    for( auto const& platform: platforms )
        window->draw(platform);

    for( auto const& cactus: cactuses )
        window->draw(cactus.sprite);

    for( auto & ptero: pteros ) {
        ptero.update();
        window->draw(ptero.sprite);
    }

    for( auto & missile : player.missiles ) {
        missile.update();
        window->draw(missile.sprite);
    }

    redrawTiles();

    player.setInfModeSpeed(velocity);
    player.update();
    playerOffset = checkMovement(&player.rect, player.desiredOffsetY);
    player.render(playerOffset);
    window->draw(player.sprite);

    // move camera
    view.move(velocity, 0);

    // check if player must die

    for( auto & cactus: cactuses )
        if (cactus.collision(player.sprite.getGlobalBounds()))
            kill();

    for( auto & ptero: pteros )
        if (ptero.collision(player.sprite.getGlobalBounds()))
            kill();

    window->setView(window->getDefaultView());
    updateScore();
    window->draw(scoreText);

    window->display();

    velocity += A;
}

void InfiniteMode::initObjects()
{
    background.setPosition(-velocity, 0);
    background.setSize(sf::Vector2f(WIN_W, WIN_H));
    background.setFillColor(sf::Color::White);

    platformTexture.loadFromFile("assets/tile.png");
    sf::Sprite tempSprite;
    tempSprite.setTexture(platformTexture);
    tempSprite.setTextureRect(sf::IntRect(0, 0, 30, 10));

    int i;
    for (i = 0; i < 50; i++) {
        tempSprite.setPosition(TILE_W * i, GROUND);
        platforms.push_back(tempSprite);
    }

    float pos = 4 * distance;
    for (i = 0; i < 5; i++) {
        auto c = new Cactus(sf::Vector2f(pos, LVL_H - GROUND));
        cactuses.push_back(*c);

        lastCactusX = pos;
        pos += random(int(distance), int(5 * distance));
    }

    for (i = 0, pos = 3000; i < 5; i++)
    {
        auto p = new Pterodactyl(sf::Vector2f(pos, LVL_H - GROUND - 200), -3);
        p->setStMode();
        pteros.push_back(*p);

        lastPteroX = pos;
        pos += random(500, 1500);
    }

    font.loadFromFile("assets/font.ttf");
    scoreText.setFont(font);
    scoreText.setString("Hello");
    scoreText.setCharacterSize(24);
    scoreText.setFillColor(GRAY);
    scoreText.setPosition(WIN_W - scoreText.getGlobalBounds().width, 0);

}

void InfiniteMode::redrawTiles()
{
    float l_border = view.getCenter().x - WIN_W / 2;

    // if tile is out of sight
    if (platforms[0].getGlobalBounds().left < l_border - TILE_W) {

        platforms.erase(platforms.begin());

        sf::Sprite tempSprite;
        tempSprite.setTexture(platformTexture);
        tempSprite.setTextureRect(sf::IntRect(0, 0, 30, 10));

        tempSprite.setPosition(platforms.back().getGlobalBounds().left + TILE_W, GROUND);
        platforms.push_back(tempSprite);

    }

    // if cactus is out of sight
    if (cactuses[0].sprite.getPosition().x < l_border - 100)
    {
        cactuses.erase(cactuses.begin());

        lastCactusX += random(int(distance), int(5 * distance));
        auto c = new Cactus(sf::Vector2f(lastCactusX, LVL_H - GROUND));
        cactuses.push_back(*c);
    }

    // if pterodactyl is out of sight
    if (cactuses[0].sprite.getPosition().x < l_border - 100)
    {
        pteros.erase(pteros.begin());

        lastPteroX += random(int(4*distance), int(20*distance));
        auto p = new Pterodactyl(sf::Vector2f(lastPteroX, LVL_H - GROUND - 200), -3);
        pteros.push_back(*p);
    }

}

int InfiniteMode::random(int a, int b)
{
    std::uniform_real_distribution<float> dist(a, b);
    return floor(dist(mt));
}

void InfiniteMode::updateScore()
{
    score = (int) player.rect.getGlobalBounds().left / 70;
    std::string sc = std::to_string(score);
    for (int i = 0, len = 5 - sc.length(); i < len; i++)
        sc.insert(0, "0"); // it`s fucking weird

    scoreText.setString("SCORE: " + sc);
    scoreText.setPosition(WIN_W - scoreText.getGlobalBounds().width - 20, 20);
}

void InfiniteMode::kill()
{
    player.dead = true;
    state = -1;
}

void InfiniteMode::reset()
{
    state = 1;
    player.dead = false;
    lastPteroX = 0;
    lastCactusX = 0;
    score = 0;
    scoreText.setString("SCORE: 0");
    velocity = 6.0;
    distance = velocity * 30;
    cactuses.clear();
    pteros.clear();
    redrawTiles();

    for (int i = 0, pos = 4 * (int) distance; i < 5; i++)
    {
        auto c = new Cactus(sf::Vector2f(pos, LVL_H - GROUND));
        cactuses.push_back(*c);

        lastCactusX = pos;
        pos += random(int(distance), int(5 * distance));
    }

    for (int i = 0, pos = 3500; i < 5; i++)
    {
        auto p = new Pterodactyl(sf::Vector2f(pos, LVL_H - GROUND - 200), -3);
        p->setStMode();
        pteros.push_back(*p);

        lastPteroX = pos;
        pos += random(500, 1500);
    }


}
