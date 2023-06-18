#ifndef ROTATABLE_WEAPON_HPP_
#define ROTATABLE_WEAPON_HPP_

#include "Weapon.hpp"

struct RotatableWeapon : Weapon {
    explicit RotatableWeapon(World &world);
    void change_angle(sf::Time, float);
    void set_angle_change_direction(float direction);

protected:
    virtual void reset();

    float m_current_angle_change_direction = 0;
    float m_angle = 0;
    bool m_is_rotation_blocked = false;

    void update_current(sf::Time delta_time) override;
    void draw_current(sf::RenderTarget &target, sf::RenderStates states) const override;

};

#endif // ROTATABLE_WEAPON_HPP_
