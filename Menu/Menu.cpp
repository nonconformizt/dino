
#include "Menu.hpp"
using namespace sf;

Menu::Menu(sf::RenderWindow * win)
{
    window = win;

    background.setPosition(0, 0);
    background.setSize(Vector2f(WIN_W, WIN_H));
    background.setFillColor(Color::White);

    font.loadFromFile("assets/font.ttf");

    title.setFont(font);
    title.setString("DINO REMASTERED_");
    title.setCharacterSize(57);
    title.setFillColor(gray);
    title.setPosition(Vector2f((WIN_W - title.getGlobalBounds().width + 20) / 2, 86));


    subtitle.setFont(font);
    subtitle.setString("BY BOGDAN KORZH");
    subtitle.setCharacterSize(23);
    subtitle.setFillColor(gray);
    subtitle.setPosition(Vector2f((WIN_W - subtitle.getGlobalBounds().width) / 2, 155));

    btn1Label.setFont(font);
    btn1Label.setString("INFINITE MODE");
    btn1Label.setCharacterSize(28);
    btn1Label.setFillColor(gray);
    btn1Label.setPosition(Vector2f((WIN_W - btn1Label.getGlobalBounds().width) / 2, 312));

    btn2Label.setFont(font);
    btn2Label.setString("LEVELS");
    btn2Label.setCharacterSize(34);
    btn2Label.setFillColor(gray);
    btn2Label.setPosition(Vector2f((WIN_W - btn2Label.getGlobalBounds().width) / 2, 445));

    btnTexture.loadFromFile("assets/button.png");
    btn1.setTexture(btnTexture);
    btn2.setTexture(btnTexture);
    btn1.setTextureRect(IntRect(0, 0, 293, 64));
    btn1.setPosition(348, 297);
    btn2.setTextureRect(IntRect(0, 0, 293, 64));
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

    for (auto & spark : sparks) {
        spark.setFillColor(gray);
        spark.setSize(Vector2f(6, 6));
    }

    levelMenu = new LevelMenu(window, &font);
    characterMenu = new CharacterMenu(window, &font);
    rating = new Rating(window, &font);
    textField = new TextField(window, &font);

}

void Menu::update()
{
    ////////////// PROCESS MOUSE MOVEMENT /////////////////

    int x = sf::Mouse::getPosition(*window).x,
        y = sf::Mouse::getPosition(*window).y,
        newActive;

    if (x != prevMouseX || y != prevMouseY)
    {
        // fucking kostyl

        if (btn1.getGlobalBounds().contains(x, y))
            newActive = 0;
        else if (btn2.getGlobalBounds().contains(x, y))
            newActive = 1;
        // yes, i know about loops, but im too lazy
        else if (smallBtns[0].getGlobalBounds().contains(x, y))
            newActive = 2;
        else if (smallBtns[1].getGlobalBounds().contains(x, y))
            newActive = 3;
        else if (smallBtns[2].getGlobalBounds().contains(x, y))
            newActive = 4;
        else
            newActive = activeBtn;

        activeChanged = (activeBtn != newActive);
        activeBtn = newActive;
    }

    prevMouseX = x;
    prevMouseY = y;


    ///////////// PROCESS KEYBOARD EVENTS ////////////////

    Event ev;
    while (window->pollEvent(ev))
    {
        if (ev.type == Event::Closed)
            window->close();
        else if (ev.key.code == Keyboard::Escape && ev.type == Event::KeyPressed)
        {
            if (rating->isShown())
                rating->hide();
            else if (levelMenu->isShown())
                levelMenu->hide();
            else if (characterMenu->isShown())
                characterMenu->hide();
            else if (textField->isShown())
                textField->hide();
            else
                window->close();
        }
        else if ((ev.key.code == Keyboard::Space || ev.key.code == Keyboard::Tab) && ev.type == Event::KeyPressed)
        {
            if (rating->isShown() || textField->isShown())
                break;

            if (levelMenu->isShown()) {
                if (!Keyboard::isKeyPressed(Keyboard::LShift) && !Keyboard::isKeyPressed(Keyboard::RShift))
                    levelMenu->navForward();
                else
                    levelMenu->navBack();
            }
            if (characterMenu->isShown())
            {
                if (!Keyboard::isKeyPressed(Keyboard::LShift) && !Keyboard::isKeyPressed(Keyboard::RShift))
                    characterMenu->navForward();
                else
                    characterMenu->navBack();
            }
            else {
                activeChanged = true;
                if (!Keyboard::isKeyPressed(Keyboard::LShift) && !Keyboard::isKeyPressed(Keyboard::RShift))
                    activeBtn = ++activeBtn % 5;
                else {
                    activeBtn = --activeBtn % 5;
                    if (activeBtn == -1)
                        activeBtn = 4;
                }
            }

        }
        else if (ev.key.code == Keyboard::Enter && ev.type == Event::KeyPressed)
        {
            if (textField->isShown())
            {
                tempPlayerName = textField->getString();
                textField->hide();
                pushHighscore();
            }
            else if (activeBtn == 0)
            {
                if (characterMenu->isShown()) {
                    character = characterMenu->getCharacter();
                    characterMenu->hide();
                    // run infinite mode
                    if (character != -1) state = 0;
                } else
                    characterMenu->show();
            }
            else if (activeBtn == 1)
            {
                if (levelMenu->isShown()) {
                    state = levelMenu->getLevel();
                    levelMenu->hide();
                } else
                    levelMenu->show();
            }
            else if (activeBtn == 2)
                rating->show();
        }
        else if (ev.mouseButton.button == Mouse::Left && ev.type == Event::MouseButtonPressed)
        {
            int x = Mouse::getPosition(*window).x,
                y = Mouse::getPosition(*window).y;

            if (levelMenu->isShown())
                state = levelMenu->mouseClicked(sf::Vector2i(x, y));
            else if (characterMenu->isShown())
            {
                character = characterMenu->mouseClicked(sf::Vector2i(x, y));
                if (character != -1) state = 0;
            }
            else
            {
                if (btn1.getGlobalBounds().contains(x, y))
                    characterMenu->show();
                else if (btn2.getGlobalBounds().contains(x, y) && !levelMenu->isShown())
                    levelMenu->show();
                else if (smallBtns[0].getGlobalBounds().contains(x, y) && !rating->isShown())
                    rating->show();
            }

        }
        else if (ev.type == sf::Event::TextEntered && textField->isShown())
        {
            textField->input(ev.text.unicode);
        }
    }

    if (activeChanged)
    {
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
    levelMenu->render();
    characterMenu->render();
    textField->render();

    window->display();
}

size_t Menu::getState()
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
        sparks[i].setPosition( (rand() % (286)) + 350,
                               (rand() % (65)) + topOffset - 10 );
    }
}

void Menu::updateSparks()
{
    int topOffset = (activeBtn) ? 435 : 297;

    for (int i = 0; i < SPARKS_N; i++)
    {
        sparks[i].move(0, -1.7);
        if (sparks[i].getPosition().y < topOffset - 50)
            sparks[i].setPosition( (rand() % (286)) + 350,
                                   (rand() % (65)) + topOffset - 10 );

        window->draw(sparks[i]);
    }
}

void Menu::writeHighscore(int score)
{
    using namespace std;
    FILE * ratingFile = fopen("assets/rating.txt", "r");
    char ch;
    int i = 0;

    string names[10] = {""};
    int scores[10] = {0};

    while (i++ < 10)
    {
        string name;
        int sc;

        while ((ch = fgetc(ratingFile)) != '\n' && ch != EOF)
                name += ch;

        fscanf(ratingFile, "%d", &sc);

        names[i] = name;
        scores[i] = sc;

        while ((ch = fgetc(ratingFile)) != '\n' && ch != EOF);

        if (ch == EOF) break;
    }

    // if highscore bigger then smallest score
    if (score > scores[i-1]) {
        // we need to push this score
        tempHigscore = score;
        // ask user for name
        textField->show();
    }

}

void Menu::pushHighscore()
{
    using namespace std;
    FILE * ratingFile = fopen("assets/rating.txt", "r");
    char ch;
    int i = 0;

    string names[10] = {""};
    int scores[10] = {0};

    while (i++ < 10)
    {
        string name;
        int sc;

        while ((ch = fgetc(ratingFile)) != '\n' && ch != EOF)
            name += ch;

        fscanf(ratingFile, "%d", &sc);

        names[i] = name;
        scores[i] = sc;

        while ((ch = fgetc(ratingFile)) != '\n' && ch != EOF);

        if (ch == EOF) break;
    }

    for (i = 0; i < 10; i++)
        if (tempHigscore >= scores[i])
            // push here
            break;

    if (i >= 10) return;

    int indexToPush = i;

    for(i = 9; i < indexToPush; i--)
    {
        scores[i] = scores[i-1];
        names[i] = names[i-1];
    }

    scores[i] = tempHigscore;
    names[i] = tempPlayerName;

    fclose(ratingFile);

    ratingFile = fopen("assets/rating.txt", "w+");

    for (i = 0; i < 10; i++)
    {
        if (!scores[i])
            break;

        fputs((names[i] + "\n").c_str(), ratingFile);
        fprintf(ratingFile, "%d", scores[i]);
    }

    fclose(ratingFile);

}
