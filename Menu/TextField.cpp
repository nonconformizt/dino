
#include "TextField.hpp"
#include <iostream>

TextField::TextField(sf::RenderWindow *win, sf::Font *f)
{
    window = win;
    font = f;

    block.setSize(sf::Vector2f(410, 150));
    block.setPosition(WIN_W / 2 - block.getSize().x / 2, 120);
    block.setFillColor(sf::Color::White);

    bg.setSize(sf::Vector2f(WIN_W, WIN_H));
    bg.setFillColor(sf::Color(83, 83, 83, 150));

    title.setString("Enter your name:");
    title.setFont(*font);
    title.setFillColor(GRAY);
    title.setCharacterSize(26);
    title.setPosition(WIN_W / 2 - title.getGlobalBounds().width / 2, 140);

    fieldBorder.setSize(sf::Vector2f(370, 44));
    fieldBorder.setPosition(WIN_W / 2 - fieldBorder.getSize().x / 2, 200);
    fieldBorder.setFillColor(GRAY);

    fieldBackground.setSize(sf::Vector2f(360, 34));
    fieldBackground.setPosition(WIN_W / 2 - fieldBackground.getSize().x / 2, 205);
    fieldBackground.setFillColor(sf::Color::White);

    fieldText.setString("Hello_world");
    fieldText.setFont(*font);
    fieldText.setFillColor(GRAY);
    fieldText.setCharacterSize(23);
    fieldText.setPosition(WIN_W / 2 - fieldText.getGlobalBounds().width / 2, 210);

}

void TextField::render()
{
    if (!shown) return;

    window->draw(bg);
    window->draw(block);
    window->draw(title);
    window->draw(fieldBorder);
    window->draw(fieldBackground);
    window->draw(fieldText);

}

void TextField::input(sf::Uint32 code)
{
    if (code >= 33 && code <= 128 && str.length() <= 12)
        str += (char) code;
    else if (code == 8) // backspace
        str = str.substr(0, str.length() - 1);

    fieldText.setString(str);
    fieldText.setPosition(WIN_W / 2 - fieldText.getGlobalBounds().width / 2, 210);

}

void TextField::hide()
{
    str = "";
    Modal::hide();
}

