#ifndef GUI_UTIL_HPP_
#define GUI_UTIL_HPP_

#include <SFML/Graphics.hpp>

namespace GuiUtil {

void shrink_to_rect_scale(sf::Sprite &sprite, float width, float height);

void center(sf::Sprite &sprite);
void center(sf::Text &text);
void center(sf::Shape &shape);

void resize(sf::Sprite &sprite, sf::Vector2<unsigned int> size);

}  // namespace GuiUtil

#endif  // GUI_UTIL_HPP_
