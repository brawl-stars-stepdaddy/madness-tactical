#include "GuiUtil.hpp"
#include "World.hpp"

namespace GuiUtil {
    void shrink_to_rect_scale(sf::Sprite &sprite, float width, float height) {
        sprite.setScale(
                width * World::SCALE / sprite.getLocalBounds().width,
                height * World::SCALE / sprite.getLocalBounds().height
        );
    }

    void center(sf::Sprite &sprite) {
        sprite.setOrigin(sprite.getLocalBounds().width / 2, sprite.getLocalBounds().height / 2);
    }

    void resize(sf::Sprite &sprite, sf::Vector2<unsigned int> size) {
        sprite.setScale(
                size.x / sprite.getLocalBounds().width,
                size.y / sprite.getLocalBounds().height
        );
    }
}
