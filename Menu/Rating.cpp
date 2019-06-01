
#include "Rating.hpp"
#include <iostream>

Rating::Rating(sf::RenderWindow * win, sf::Font * f)
{
    window = win;
    font = f;

    blockTex.loadFromFile("assets/rating-container.png");
    block.setTexture(blockTex);
    block.setTextureRect(sf::IntRect(0, 0, 400, 500));
    block.setPosition(295, 50);

    bg.setSize(sf::Vector2f(WIN_W, WIN_H));
    bg.setFillColor(sf::Color(83, 83, 83, 150));

    title.setFont(*font);
    title.setFillColor(GRAY);
    title.setCharacterSize(29);
    title.setPosition(424, 63);
    title.setString("Rating");


    for(int i = 0, offset = 105; i < 10; i++, offset += 43)
    {
        listText[i].setCharacterSize(21);
        listText[i].setFont(*font);
        listText[i].setFillColor(GRAY);
        listText[i].setPosition(360, offset + 3);
        listText[i].setString("");

        listNum[i].setCharacterSize(21);
        listNum[i].setFont(*font);
        listNum[i].setFillColor((i < 3) ? sf::Color::White : GRAY);
        if (i == 0)
            listNum[i].setPosition(323, offset + 3);
        else if (i == 9)
            listNum[i].setPosition(315, offset + 3);
        else
            listNum[i].setPosition(320, offset + 3);
        listNum[i].setString((i == 9) ? "10" : std::to_string(i + 1));

        listBullet[i].setSize(sf::Vector2f(30, 30));
        listBullet[i].setPosition(315, offset);
        listBullet[i].setFillColor((i < 3) ? GRAY : LIGHT_GRAY);
    }

    readRating();

    for (int i = 0; i < SP_N; i++) {
        sparks[i].setFillColor(sf::Color::White);
        sparks[i].setSize(sf::Vector2f(6, 6));
    }
    initSparks();
}

void Rating::render()
{
    if (shown)
    {
        window->draw(bg);
        updateSparks();
        window->draw(block);
        window->draw(title);

        for(int i = 0; i < 10; i++)
        {
            window->draw(listText[i]);
            window->draw(listBullet[i]);
            window->draw(listNum[i]);
        }
    }
}

void Rating::readRating()
{
    using namespace std;
    FILE * mapFile = fopen("assets/rating.txt", "r");
    char ch;
    int i = 0;

    while (i < 10)
    {
        string name;
        int score, length = 0;

        while ((ch = fgetc(mapFile)) != '\n' && ch != EOF)
            if (length++ <= 13)
                name += ch;

        fscanf(mapFile, "%d", &score);

        while ((ch = fgetc(mapFile)) != '\n' && ch != EOF)
            ; // skip to the end of the line

        listText[i++].setString(name + " - " + to_string(score));

        if (ch == EOF)
            break;
    }
}

void Rating::initSparks()
{
    for (int i = 0; i < SP_N; i++) {
        sparks[i].setPosition( (rand() % 390) + 295,
                               (rand() % 70) + 50);
    }
}

void Rating::updateSparks()
{
    for (int i = 0; i < SP_N; i++)
    {
        sparks[i].move(0, -1.7);
        if (sparks[i].getPosition().y < 10)
            sparks[i].setPosition( (rand() % 390) + 295,
                                   (rand() % 70) + 50);

        window->draw(sparks[i]);
    }
}
