#ifndef CHARACTER_HPP_
#define CHARACTER_HPP_

#include <box2d/box2d.h>
#include <SFML/Graphics.hpp>
#include "Entity.hpp"
#include "WeaponEffect.hpp"

struct Character : Entity {
public:
    Character(b2World*, float, float);

    void apply_weapon_effect(WeaponEffect &);

private:
    SceneNode* m_parent;

    b2Body *m_body;
    sf::Sprite m_sprite;
    int m_health_points = 100;
    bool m_is_active = true;
    bool m_is_standing = true;

    virtual void draw_current(sf::RenderTarget &, sf::RenderStates) const final;

    virtual void update_current(sf::Time delta_time) final;

};

#endif //CHARACTER_HPP_
