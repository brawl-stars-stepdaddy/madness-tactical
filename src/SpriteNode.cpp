#include "SpriteNode.hpp"

SpriteNode::SpriteNode(const sf::Texture &texture) {
    m_sprite.setTexture(texture);
}

SpriteNode::SpriteNode(const sf::Texture &texture, const sf::IntRect &rect) {
    m_sprite.setTexture(texture);
    m_sprite.setTextureRect(rect);
}

void SpriteNode::draw_current(sf::RenderTarget &target, sf::RenderStates states)
    const {
    target.draw(m_sprite, states);
}