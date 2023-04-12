#ifndef BOX_HPP_
#define BOX_HPP_

#include "Entity.hpp"
#include "RectBody.hpp"
#include "World.hpp"

struct Box : Entity {
public:
    RectBody &get_body() override;
    EntityType get_type() override;

    void on_collision(Entity *) override;
    void on_explosion(const Explosion &) override;

protected:
    sf::Sprite m_sprite;
    RectBody m_body;

private:
    void draw_current(sf::RenderTarget &target, sf::RenderStates)
        const override;

    void update_current(sf::Time delta_time) override;
};

#endif  // BOX_HPP_
