
#include "CharacterMenu.hpp"

CharacterMenu::CharacterMenu(sf::RenderWindow *win, sf::Font *f)
{
    window = win;
    font = f;

    block.setPosition(116, 70);
    block.setSize(sf::Vector2f(740, 430));
    block.setFillColor(sf::Color::White);

    bg.setSize(sf::Vector2f(WIN_W, WIN_H));
    bg.setFillColor(sf::Color(83, 83, 83, 150));

    title.setString("Choose your fighter");
    title.setFont(*font);
    title.setFillColor(sf::Color(83, 83, 83));
    title.setCharacterSize(34);
    title.setPosition(WIN_W / 2 - title.getGlobalBounds().width / 2, 100);
}

void CharacterMenu::render()
{
    if (!shown) return;

    window->draw(bg);
    window->draw(block);
    window->draw(title);
}
