
#include "CharacterMenu.hpp"
#include <iostream>

CharacterMenu::CharacterMenu(sf::RenderWindow *win, sf::Font *f)
{
    window = win;
    font = f;

    block.setSize(sf::Vector2f(600, 330));
    block.setPosition(WIN_W / 2 - block.getSize().x / 2, 120);
    block.setFillColor(sf::Color::White);

    bg.setSize(sf::Vector2f(WIN_W, WIN_H));
    bg.setFillColor(sf::Color(83, 83, 83, 150));

    title.setString("Choose your fighter");
    title.setFont(*font);
    title.setFillColor(sf::Color(83, 83, 83));
    title.setCharacterSize(34);
    title.setPosition(WIN_W / 2 - title.getGlobalBounds().width / 2, 150);

    charactersTex[0].loadFromFile("assets/player1.png");
    charactersTex[1].loadFromFile("assets/player2.png");
    charactersTex[2].loadFromFile("assets/player3.png");

    characterListTex.loadFromFile("assets/level-container.png");

    for (int i = 0, left = 320; i < 3; i++, left += 125)
    {
        characterListBoxes[i].setTexture(characterListTex);
        characterListBoxes[i].setPosition(left, 250);
        characterListBoxes[i].setTextureRect(sf::IntRect(0, 0, 105, 106));

        characters[i].setTextureRect(sf::IntRect(0, 0, 64, 72));
        characters[i].setTexture(charactersTex[i]);
        characters[i].setPosition(left + 20, 265);
    }


}

void CharacterMenu::render()
{
    if (!shown) return;

    ////////////// PROCESS MOUSE MOVEMENT /////////////////

    int x = sf::Mouse::getPosition(*window).x,
        y = sf::Mouse::getPosition(*window).y;

    if (x != prevMouseX || y != prevMouseY)
    {
        activeCharacter = -1;
        for (int i = 0; i < 3; i++)
            if (characterListBoxes[i].getGlobalBounds().contains(x, y))
                activeCharacter = i;
    }

    prevMouseX = x;
    prevMouseY = y;

    ///////////////////////////////////////////////////////

    window->draw(bg);
    window->draw(block);
    window->draw(title);

    for ( int i = 0; i < 3; i++ )
    {
        characterListBoxes[i].setTextureRect(sf::IntRect((i == activeCharacter) ? 210 : 0, 0, 105, 106));
        window->draw(characterListBoxes[i]);
    }

    for ( const auto & ch : characters)
        window->draw(ch);

}

int CharacterMenu::mouseClicked(sf::Vector2i pos)
{
    if (!block.getGlobalBounds().contains(pos.x, pos.y))
        // clicked on background
        shown = false;
    else
    {
        for (int i = 0; i < 3; i++)
            if (characterListBoxes[i].getGlobalBounds().contains(pos.x, pos.y))
            {
                activeCharacter = i;
                shown = false;
            }
    }

    return activeCharacter;
}
