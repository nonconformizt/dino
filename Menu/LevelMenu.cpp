
#include "LevelMenu.hpp"


LevelMenu::LevelMenu(sf::RenderWindow *win, sf::Font *f)
{
    window = win;
    font = f;

    /**
     *    Load data from database somewhere here...
     */

    block.setPosition(86 + 30, 70);
    block.setSize(sf::Vector2f(740, 470));
    block.setFillColor(sf::Color::White);

    bg.setSize(sf::Vector2f(WIN_W, WIN_H));
    bg.setFillColor(sf::Color(83, 83, 83, 150));

    title.setString("Choose level:");
    title.setFillColor(sf::Color(83, 83, 83));
    title.setCharacterSize(34);
    title.setPosition(340, 100);
    title.setFont(*font);

    levelListTex.loadFromFile("assets/level-container.png");

    for (int i = 0, left = 185; i < 5; i++, left += 105 + 20)
    {
        levelListBoxes[i].setTexture(levelListTex);
        levelListBoxes[i].setPosition(left, 164);
        levelListBoxes[i].setTextureRect(sf::IntRect(0, 0, 105, 106));
    }

}

void LevelMenu::render()
{
    if (shown)
    {
        window->draw(bg);
        window->draw(block);
        window->draw(title);

        for (int i = 0; i < 5; i++)
            window->draw(levelListBoxes[i]);
    }

}
