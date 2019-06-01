
#ifndef DINO_TEXTFIELD_HPP
#define DINO_TEXTFIELD_HPP

#include "Modal.hpp"

class TextField : public Modal {

public:
    TextField(sf::RenderWindow * win, sf::Font * f);
    void render() final;

private:

    sf::RectangleShape block;

};


#endif //DINO_TEXTFIELD_HPP
