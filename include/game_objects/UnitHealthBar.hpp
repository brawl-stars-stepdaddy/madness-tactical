#ifndef UNIT_HEALTH_BAR_HPP_
#define UNIT_HEALTH_BAR_HPP_

#include "SceneNode.hpp"

struct Unit;
struct World;

struct UnitHealthBar : SceneNode {
    explicit UnitHealthBar(World &world, Unit *parent, const sf::Font &font);
    sf::Text get_text();

private:
    void draw_current(sf::RenderTarget &target, sf::RenderStates)
        const override;

    void update_current(sf::Time delta_time) override;

    Unit *m_parent;
    float m_direction = 1.0f;
    sf::Text m_text;
};

#endif  // UNIT_HEALTH_BAR_HPP_
