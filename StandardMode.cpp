
#include "StandardMode.hpp"

StandardMode::StandardMode(sf::RenderWindow * win)
{
    window = win;
    initObjects();

    view.setCenter( (float) window->getSize().x / 2, (float) window->getSize().y / 2);
    view.setSize(window->getSize().x, window->getSize().y);
    window->setView(view);

    player.setStandartMode(true);

    mt.seed(time(nullptr)*time(nullptr));
}


float StandardMode::checkMovement(const sf::RectangleShape * rect, float offset)
{
    // always can go up
    if (offset <= 0)
        return offset;

    float bottom = rect->getPosition().y + rect->getSize().y;

    if (bottom + offset > GROUND)
        return GROUND - bottom;

    return offset;
}

void StandardMode::update()
{
    sf::Event event;
    while (window->pollEvent(event))
    {
        if (event.type == sf::Event::Closed || event.key.code == sf::Keyboard::Escape)
            window->close();
    }

    window->clear();

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

    player.setStModeSpeed(velocity);
    player.update();
    playerOffset = checkMovement(&player.rect, player.desiredOffestY);
    player.render(playerOffset);
    window->draw(player.sprite);

    // move camera
    view.move(velocity, 0);
    window->setView(view);

    // check if player must die

    for( auto & cactus: cactuses )
        if (cactus.collision(player.sprite.getGlobalBounds()))
            window->close();

    for( auto & ptero: pteros )
        if (ptero.collision(player.sprite.getGlobalBounds()))
            /* player is dead */;

    window->display();

    velocity += A;
}

void StandardMode::initObjects()
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
        auto c = new Cactus(sf::Vector2f(pos, WIN_H - GROUND));
        cactuses.push_back(*c);

        lastCactusX = pos;
        pos += random(int(distance), int(5 * distance));
    }

}

void StandardMode::redrawTiles()
{
    float left = view.getCenter().x - WIN_W / 2;

    // if tile is out of sight
    if (platforms[0].getGlobalBounds().left < left - TILE_W) {

        platforms.erase(platforms.begin());

        sf::Sprite tempSprite;
        tempSprite.setTexture(platformTexture);
        tempSprite.setTextureRect(sf::IntRect(0, 0, 30, 10));

        tempSprite.setPosition(platforms.back().getGlobalBounds().left + TILE_W, GROUND);
        platforms.push_back(tempSprite);
    }

    // if cactus is out of sight
//    if (platforms[0].getGlobalBounds().left < left - TILE_W) {
//
//        platforms.erase(platforms.begin());
//
//        sf::Sprite tempSprite;
//        tempSprite.setTexture(platformTexture);
//        tempSprite.setTextureRect(sf::IntRect(0, 0, 30, 10));
//
//        tempSprite.setPosition(platforms.back().getGlobalBounds().left + TILE_W, GROUND);
//        platforms.push_back(tempSprite);
//    }

}

int StandardMode::random(int a, int b)
{
    std::uniform_real_distribution<float> dist(a, b);
    return floor(dist(mt));
}
