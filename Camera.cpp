
#include "Camera.hpp"

Camera::Camera(sf::RenderWindow * win, sf::RectangleShape * rect)
{
    window = win;
    player = rect;

    view.setCenter( (float) window->getSize().x / 2, (float) window->getSize().y / 2);
    view.setSize(window->getSize().x, window->getSize().y);
    window->setView(view);

}

void Camera::update()
{
    auto pos = player->getPosition();
    sf::Vector2f center;

    if (pos.x < WIN_W / 2) {
        center.x = WIN_W / 2;
    } else if (pos.x > (LVL_W - WIN_W / 2)) {
        center.x = LVL_W - WIN_W / 2;
    } else {
        center.x = pos.x;
    }

    if (pos.y < WIN_H / 2) {
        center.y = WIN_H / 2;
    } else if (pos.y > (LVL_H - WIN_H / 2)) {
        center.y = LVL_H - WIN_H / 2;
    } else {
        center.y = pos.y;
    }

    view.setCenter(center);
    window->setView(view);

}
