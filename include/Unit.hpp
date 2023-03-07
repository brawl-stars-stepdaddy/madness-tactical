#ifndef UNIT_HPP_
#define UNIT_HPP_

#include "Entity.hpp"
#include "ResourceIdentifiers.hpp"

struct Unit : Entity {
public:
    enum class Type {
        ENGINEER,
    };

    Unit(Type type, const TextureHolder &textureHolder);

    virtual void draw_current(sf::RenderTarget &target, sf::RenderStates) const;

private:
    sf::Sprite m_sprite;
    Type m_type;
};

#endif