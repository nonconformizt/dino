
#include "LevelMenu.hpp"


LevelMenu::LevelMenu(sf::RenderWindow *win, sf::Font *f)
{
    window = win;
    font = f;

    /**
     *    Load data about level passing somewhere here...
     */

    block.setPosition(116, 70);
    block.setSize(sf::Vector2f(740, 430));
    block.setFillColor(sf::Color::White);

    bg.setSize(sf::Vector2f(WIN_W, WIN_H));
    bg.setFillColor(sf::Color(83, 83, 83, 150));

    title.setString("Choose level:");
    title.setFillColor(sf::Color(83, 83, 83));
    title.setCharacterSize(34);
    title.setPosition(340, 100);
    title.setFont(*font);

    levelListTex.loadFromFile("assets/level-container.png");
    levelStarTex.loadFromFile("assets/star.png");
    levelSmallStarTex.loadFromFile("assets/star-small.png");

    for (int j = 0, left = 185, top = 190; j < MAX_LVLS; j++, left += 125)
    {
        if (j == 5) {
            left = 185;
            top = 330;
        }

        levelListBoxes[j].setTexture(levelListTex);
        levelListBoxes[j].setPosition(left, top);
        levelListBoxes[j].setTextureRect(sf::IntRect(0, 0, 105, 106));
    }

    for (int i = 0, left = 185; i < LVLS_N; i++, left += 125)
    {

        levelListNums[i].setFont(*font);
        levelListNums[i].setPosition((i == 0) ? (left + 40) : (left + 30), 189);
        levelListNums[i].setFillColor(GRAY);
        levelListNums[i].setCharacterSize(52);
        levelListNums[i].setString(std::to_string(i+1));

        levelStars[i][0].setPosition(left + 8, 260);
        levelStars[i][0].setTexture(levelSmallStarTex);
        levelStars[i][0].setTextureRect(sf::IntRect(28, 0, 28, 28));

        levelStars[i][1].setPosition(left + 37, 252);
        levelStars[i][1].setTexture(levelStarTex);
        levelStars[i][1].setTextureRect(sf::IntRect(34, 0, 34, 36));

        levelStars[i][2].setPosition(left + 70, 260);
        levelStars[i][2].setTexture(levelSmallStarTex);
        levelStars[i][2].setTextureRect(sf::IntRect(28, 0, 28, 28));

    }

    for (auto & spark : sparks) {
        spark.setFillColor(sf::Color::White);
        spark.setSize(sf::Vector2f(6, 6));
    }
    initSparks();

}

void LevelMenu::render()
{
    if (!shown)
        return;

    ////////////// PROCESS MOUSE MOVEMENT /////////////////

    int x = sf::Mouse::getPosition(*window).x,
        y = sf::Mouse::getPosition(*window).y;

    if (x != prevMouseX || y != prevMouseY)
    {
        for (int i = 0; i < LVLS_N; i++)
            if (levelListBoxes[i].getGlobalBounds().contains(x, y))
                activeLevel = i + 1;
    }

    prevMouseX = x;
    prevMouseY = y;


    window->draw(bg);
    updateSparks();
    window->draw(block);
    window->draw(title);

    redrawStars();

    for (const auto & listBox : levelListBoxes)
        window->draw(listBox);

    for (int i = 0; i < LVLS_N; i++) {

        window->draw(levelListNums[i]);

        for (const sf::Sprite & s : levelStars[i])
            window->draw(s);

        if ((i + 1) == activeLevel) {
            levelListBoxes[i].setTextureRect(sf::IntRect(105, 0, 105, 106));
            levelListNums[i].setFillColor(sf::Color::White);
        } else {
            levelListBoxes[i].setTextureRect(sf::IntRect(0, 0, 105, 106));
            levelListNums[i].setFillColor(GRAY);
        }
    }

}

void LevelMenu::redrawStars()
{
    for (int i = 0, left = 185; i < LVLS_N; i++, left += 105 + 20)
    {
        if (levelCollectedStars[i] >= 1)  {
            // make star active
            if ((i + 1) == activeLevel) // exactly this level chosen
                levelStars[i][0].setTextureRect(sf::IntRect(56, 0, 28, 28));
            else
                levelStars[i][0].setTextureRect(sf::IntRect(0, 0, 28, 28));
        }
        else
            levelStars[i][0].setTextureRect(sf::IntRect(28, 0, 28, 28));

        if (levelCollectedStars[i] >= 2)  {
            if ((i + 1) == activeLevel)
                levelStars[i][1].setTextureRect(sf::IntRect(68, 0, 34, 36));
            else
                levelStars[i][1].setTextureRect(sf::IntRect(0, 0, 34, 36));
        }
        else
            levelStars[i][1].setTextureRect(sf::IntRect(34, 0, 34, 36));

        if (levelCollectedStars[i] >= 3)  {
            if ((i + 1) == activeLevel)
                levelStars[i][2].setTextureRect(sf::IntRect(56, 0, 28, 28));
            else
                levelStars[i][2].setTextureRect(sf::IntRect(0, 0, 28, 28));
        }
        else
            levelStars[i][2].setTextureRect(sf::IntRect(28, 0, 28, 28));

    }
}

void LevelMenu::initSparks()
{
    for (int i = 0; i < SPARKS; i++) {
        sparks[i].setPosition( (rand() % 740) + 116,
                               (rand() % 70) + 50);
    }
}

void LevelMenu::updateSparks()
{
    for (int i = 0; i < SPARKS; i++)
    {
        sparks[i].move(0, -1.7);
        if (sparks[i].getPosition().y < 20)
            sparks[i].setPosition( (rand() % 740) + 116,
                                   (rand() % 70) + 50);

        window->draw(sparks[i]);
    }
}

int LevelMenu::mouseClicked(sf::Vector2i pos)
{
    for (int i = 0; i < LVLS_N; i++)
        if (levelListBoxes[i].getGlobalBounds().contains(pos.x, pos.y))
            return i + 1;

    return -1;
}
