#ifndef SCENE_SPRITE_HPP_
#define SCENE_SPRITE_HPP_

#include <SFML/Graphics.hpp>
#include "SceneNode.hpp"

struct SpriteNode : SceneNode {
public:
    explicit SpriteNode(World &world, const sf::Texture &texture);
    SpriteNode(
        World &world,
        const sf::Texture &texture,
        const sf::IntRect &rect
    );

    sf::Sprite get_sprite() {
        return m_sprite;
    }

private:
    virtual void draw_current(sf::RenderTarget &target, sf::RenderStates states)
        const override;

    sf::Sprite m_sprite;
};

#endif
