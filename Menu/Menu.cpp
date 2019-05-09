
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

    btnTexture.loadFromFile("assets/button.png");
    btn1.setTexture(btnTexture);
    btn2.setTexture(btnTexture);
    btn1.setTextureRect(sf::IntRect(0, 0, 293, 64));
    btn1.setPosition(348, 297);
    btn2.setTextureRect(sf::IntRect(0, 0, 293, 64));
    btn2.setPosition(348, 435);

    smallBtnTexture[0].loadFromFile("assets/btn-rating.png");
    smallBtnTexture[1].loadFromFile("assets/btn-achieve.png");
    smallBtnTexture[2].loadFromFile("assets/btn-about.png");

    smallBtns[0].setTexture(smallBtnTexture[0]);
    smallBtns[1].setTexture(smallBtnTexture[1]);
    smallBtns[2].setTexture(smallBtnTexture[2]);

    smallBtns[0].setPosition(sf::Vector2f(913, 379));
    smallBtns[1].setPosition(sf::Vector2f(913, 448));
    smallBtns[2].setPosition(sf::Vector2f(913, 525));

    smallBtns[0].setTextureRect(sf::IntRect(0, 0, 55, 55));
    smallBtns[1].setTextureRect(sf::IntRect(0, 0, 55, 55));
    smallBtns[2].setTextureRect(sf::IntRect(0, 0, 55, 55));

    for (int i = 0; i < SPARKS_N; i++) {
        sparks[i].setFillColor(gray);
        sparks[i].setSize(sf::Vector2f(6, 6));
    }

    rating = new Rating(window, &font);
}

void Menu::update()
{
    // Process events
    sf::Event event;
    while (window->pollEvent(event))
    {
        if (event.type == sf::Event::Closed)
            window->close();
        else if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape) {
            if (rating->isShown())
                rating->hide();
            else
                window->close();
        }
        else if (event.type == sf::Event::KeyPressed &&
                 (event.key.code == sf::Keyboard::Space || event.key.code == sf::Keyboard::Tab)) {
            activeChanged = true;
            if (!sf::Keyboard::isKeyPressed(sf::Keyboard::LShift) && !sf::Keyboard::isKeyPressed(sf::Keyboard::RShift))
                activeBtn = ++activeBtn % 5;
            else {
                activeBtn = --activeBtn % 5;
                if (activeBtn == -1)
                    activeBtn = 4;
            }
        } else if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Enter) {
            if (activeBtn == 0)
                state = 0;
            else if (activeBtn == 1)
                state = 1;
            else if (activeBtn == 2)
                rating->show();
        }
    }


    if (activeChanged) {
        deactivateAll();
        switch (activeBtn) {
            case 0:
                initSparks();
                btn1.setTextureRect(sf::IntRect(293, 0, 293, 64));
                btn1Label.setFillColor(sf::Color::White);
                break;
            case 1:
                initSparks();
                btn2.setTextureRect(sf::IntRect(293, 0, 293, 64));
                btn2Label.setFillColor(sf::Color::White);
                break;
            case 2:
                smallBtns[0].setTextureRect(sf::IntRect(55, 0, 55, 55));
                break;
            case 3:
                smallBtns[1].setTextureRect(sf::IntRect(55, 0, 55, 55));
                break;
            case 4:
                smallBtns[2].setTextureRect(sf::IntRect(55, 0, 55, 55));
                break;
        }
        activeChanged = false;
    }

    window->clear();
    window->draw(background);

    if (activeBtn == 0 || activeBtn == 1) {
        updateSparks();
    }

    window->draw(title);
    window->draw(subtitle);
    window->draw(btn1);
    window->draw(btn2);
    window->draw(btn1Label);
    window->draw(btn2Label);
    window->draw(smallBtns[0]);
    window->draw(smallBtns[1]);
    window->draw(smallBtns[2]);

    rating->render();

    window->display();
}

int Menu::getState()
{
    return state;
}

void Menu::deactivateAll()
{
    btn1.setTextureRect(sf::IntRect(0, 0, 293, 64));
    btn2.setTextureRect(sf::IntRect(0, 0, 293, 64));
    btn1Label.setFillColor(gray);
    btn2Label.setFillColor(gray);

    for (int i = 0; i < 3; i++)
        smallBtns[i].setTextureRect(sf::IntRect(0, 0, 55, 55));
}

void Menu::initSparks()
{
    int topOffset = (activeBtn) ? 435 : 297;

    for (int i = 0; i < SPARKS_N; i++) {
        sparks[i].setPosition( (rand() % (297 + 1)) + 340,
                               (rand() % (64 + 1)) + topOffset - 10 );
    }

}

void Menu::updateSparks()
{
    int topOffset = (activeBtn) ? 435 : 297;

    for (int i = 0; i < SPARKS_N; i++)
    {
        sparks[i].move(0, -1.7);
        if (sparks[i].getPosition().y < topOffset - 50)
            sparks[i].setPosition( (rand() % (297 + 1)) + 340,
                                   (rand() % (64 + 1)) + topOffset - 10 );

        window->draw(sparks[i]);
    }

}
