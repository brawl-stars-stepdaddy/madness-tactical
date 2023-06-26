#include "utils/GuiUtil.hpp"
#include "logic/World.hpp"

namespace GuiUtil {
void shrink_to_rect_scale(sf::Sprite &sprite, float width, float height) {
    sprite.setScale(
        width * World::SCALE / sprite.getLocalBounds().width,
        height * World::SCALE / sprite.getLocalBounds().height
    );
}

void center(sf::Sprite &sprite) {
    sprite.setOrigin(
        sprite.getLocalBounds().width / 2, sprite.getLocalBounds().height / 2
    );
}

void center(sf::Text &text) {
    text.setOrigin(
        text.getLocalBounds().width / 2, text.getLocalBounds().height / 2
    );
}

void center(sf::Shape &shape) {
    shape.setOrigin(
        shape.getLocalBounds().width / 2, shape.getLocalBounds().height / 2
    );
}

void resize(sf::Sprite &sprite, sf::Vector2<unsigned int> size) {
    sprite.setScale(
        size.x / sprite.getLocalBounds().width,
        size.y / sprite.getLocalBounds().height
    );
}
}  // namespace GuiUtil
