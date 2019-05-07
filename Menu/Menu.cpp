
#include "Menu.hpp"

Menu::Menu(sf::RenderWindow * win)
{
    window = win;

    background.setPosition(0, 0);
    background.setSize(sf::Vector2f(WIN_W, WIN_H));
    background.setFillColor(sf::Color::White);

    font.loadFromFile("assets/font.ttf");

    title.setFont(font);
    title.setString("DINO REMASTERED_");
    title.setCharacterSize(57);
    title.setFillColor(gray);
    title.setPosition(sf::Vector2f((WIN_W - title.getGlobalBounds().width + 20) / 2, 86));


    subtitle.setFont(font);
    subtitle.setString("BY BOGDAN KORZH");
    subtitle.setCharacterSize(23);
    subtitle.setFillColor(gray);
    subtitle.setPosition(sf::Vector2f((WIN_W - subtitle.getGlobalBounds().width) / 2, 155));

    btn1Label.setFont(font);
    btn1Label.setString("STANDART MODE");
    btn1Label.setCharacterSize(23);
    btn1Label.setFillColor(gray);
    btn1Label.setPosition(sf::Vector2f((WIN_W - btn1Label.getGlobalBounds().width) / 2, 315));

    btn2Label.setFont(font);
    btn2Label.setString("LEVELS");
    btn2Label.setCharacterSize(34);
    btn2Label.setFillColor(gray);
    btn2Label.setPosition(sf::Vector2f((WIN_W - btn2Label.getGlobalBounds().width) / 2, 445));

    sf::Texture t;
    t.loadFromFile("assets/button.png");
    btn1.setTexture(t);
    btn2.setTexture(t);
    btn1.setTextureRect(sf::IntRect(0, 0, 293, 64));
    btn2.setTextureRect(sf::IntRect(0, 0, 293, 64));

}

void Menu::update()
{
    // Process events
    sf::Event event;
    while (window->pollEvent(event))
    {
        if (event.type == sf::Event::Closed || event.key.code == sf::Keyboard::Escape)
            window->close();
        else if (event.type == sf::Event::KeyReleased &&
                    (event.key.code == sf::Keyboard::Space || event.key.code == sf::Keyboard::Right))
            {} // next button
    }

    window->clear();
    window->draw(background);

    window->draw(title);
    window->draw(subtitle);
    window->draw(btn1);
    window->draw(btn2);
    window->draw(btn1Label);
    window->draw(btn2Label);

    window->display();
}

int Menu::getState()
{
    return state;
}
