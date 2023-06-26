#ifndef UNIT_HEALTH_BAR_HPP_
#define UNIT_HEALTH_BAR_HPP_

#include "SceneNode.hpp"

struct Unit;
struct World;

struct UnitHealthBar : SceneNode {
public:
    explicit UnitHealthBar(World &world, Unit *parent, const sf::Font &font);

    sf::Text get_text();

private:
    void draw_current(sf::RenderTarget &target, sf::RenderStates states) const override;
    void update_current(sf::Time delta_time) override;

    float m_direction = 1.0f;
    Unit *m_parent;
    sf::Text m_text;
};

#endif  // UNIT_HEALTH_BAR_HPP_
