
#include "TextField.hpp"
#include <iostream>

TextField::TextField(sf::RenderWindow *win, sf::Font *f)
{
    window = win;
    font = f;

    block.setSize(sf::Vector2f(600, 330));
    block.setPosition(WIN_W / 2 - block.getSize().x / 2, 120);
    block.setFillColor(sf::Color::White);

    bg.setSize(sf::Vector2f(WIN_W, WIN_H));
    bg.setFillColor(sf::Color(83, 83, 83, 150));

    title.setString("Enter your name:");
    title.setFont(*font);
    title.setFillColor(sf::Color(83, 83, 83));
    title.setCharacterSize(34);
    title.setPosition(WIN_W / 2 - title.getGlobalBounds().width / 2, 150);

    shown = true;

}

void TextField::render()
{
    if (!shown) return;

    window->draw(bg);
    window->draw(block);
    window->draw(title);

}

void TextField::input(sf::Uint32 code)
{
    if (code >= 33 && code <= 128 && str.length() <= 12)
        str += (char) code;
    else if (code == 8) // backspace
        str = str.substr(0, str.length() - 1);

    std::cout << str << std::endl;
}

void TextField::hide()
{
    str = "";
    Modal::hide();
}

