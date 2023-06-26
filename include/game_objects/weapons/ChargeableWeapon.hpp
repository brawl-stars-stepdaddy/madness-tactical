#ifndef CHARGEABLE_WEAPON_HPP_
#define CHARGEABLE_WEAPON_HPP_

#include "RotatableWeapon.hpp"

struct ChargeableWeapon : RotatableWeapon {
public:
    explicit ChargeableWeapon(World &world);

    void charge(sf::Time delta_time);
    void set_currently_charging(bool is_charging);

protected:
    void update_current(sf::Time delta_time) override;
    void draw_current(sf::RenderTarget &target, sf::RenderStates states) const override;

    bool m_is_charging = false;
    float m_init_charge_level = 0.1f;
    float m_charge_level = m_init_charge_level;
};

#endif  // CHARGEABLE_WEAPON_HPP_
