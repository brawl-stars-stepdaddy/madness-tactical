#ifndef BODY_HPP_
#define BODY_HPP_

#include <SFML/Graphics.hpp>

struct Body {
    sf::Vector2f get_position();
    float get_rotation();

private:
    // TODO --- box2d wrap
    sf::Vector2f m_position = {0, 0};
    float m_rotation = 0;
};

#endif