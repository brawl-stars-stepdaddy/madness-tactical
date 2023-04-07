#ifndef UNIT_HPP_
#define UNIT_HPP_

#include "Entity.hpp"
#include "ResourceIdentifiers.hpp"
#include "RectBody.hpp"
#include "World.hpp"
#include "UnitBody.hpp"

struct World;

struct Unit : Entity {
public:
    enum class Type {
        ENGINEER,
    };

    Unit(Type type, World &world, const TextureHolder &textureHolder, std::pair<float, float>);

    UnitBody &get_body() override;

private:
    void draw_current(sf::RenderTarget &target, sf::RenderStates)
    const override;

    void update_current(sf::Time delta_time) override;

    sf::Sprite m_sprite;
    Type m_type;
    UnitBody m_body;
};

#endif