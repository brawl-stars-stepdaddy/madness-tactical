#include "game_objects/SpriteNode.hpp"

SpriteNode::SpriteNode(World &world, const sf::Texture &texture)
    : SceneNode(world) {
    m_sprite.setTexture(texture);
}

SpriteNode::SpriteNode(
    World &world,
    const sf::Texture &texture,
    const sf::IntRect &rect
)
    : SceneNode(world) {
    m_sprite.setTexture(texture);
    m_sprite.setTextureRect(rect);
}

void SpriteNode::draw_current(sf::RenderTarget &target, sf::RenderStates states)
    const {
    target.draw(m_sprite, states);
}

sf::Sprite SpriteNode::get_sprite() {
    return m_sprite;
}
