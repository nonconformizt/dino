
#ifndef DINO_TEXTFIELD_HPP
#define DINO_TEXTFIELD_HPP

#include "Modal.hpp"

class TextField : public Modal {

public:
    TextField(sf::RenderWindow * win, sf::Font * f);
    void render() final;
    void input(sf::Uint32 code);
    std::string getString() { return str; }

private:
    void hide();

    sf::RectangleShape block;
    std::string str;

};


#endif //DINO_TEXTFIELD_HPP
