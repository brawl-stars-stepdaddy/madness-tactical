#ifndef WEAPON_HPP_
#define WEAPON_HPP_

#include <vector>
#include "Projectile.hpp"
#include "SFML/Graphics.hpp"
#include "SceneNode.hpp"

enum WeaponType {
    BAZOOKA,
    GRENADE,
    CONCRETE_DONKEY
};

const int WEAPON_TYPES_NUMBER = 3;

struct Unit;

struct Weapon : SceneNode {
    virtual void charge(sf::Time) = 0;
    virtual void change_angle(sf::Time, float) = 0;
    virtual void launch(World &) = 0;
    virtual void set_angle_change_direction(float direction);
    virtual void set_currently_charging(bool is_charging);
    virtual void set_hidden(bool);

protected:
    virtual void reset();

    Unit *m_parent;

    float m_current_angle_change_direction = 0;
    bool m_is_charging = false;
    bool m_is_hidden = true;
private:
    void update_current(sf::Time delta_time) override;
    void draw_current(sf::RenderTarget &target, sf::RenderStates states)
        const override;


};

#endif  // WEAPON_HPP_
