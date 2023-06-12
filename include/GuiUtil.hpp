#ifndef MADNESS_TACTICAL_GUIUTIL_HPP
#define MADNESS_TACTICAL_GUIUTIL_HPP

#include <SFML/Graphics.hpp>

namespace GuiUtil {
    void shrink_to_rect_scale(sf::Sprite &sprite, float width, float height);

    void center(sf::Sprite &sprite);

    void resize(sf::Sprite &sprite, sf::Vector2<unsigned int> size);
}

#endif //MADNESS_TACTICAL_GUIUTIL_HPP
