#include "Weapon.hpp"
#include "Unit.hpp"

Weapon::Weapon(World &world) : SceneNode(world) {

}

void Weapon::update_current(sf::Time delta_time) {
    if (m_is_charging) {
        charge(delta_time);
    }
    change_angle(delta_time, m_current_angle_change_direction);
    reset();
}

void Weapon::draw_current(sf::RenderTarget &target, sf::RenderStates states)
    const {
}

void Weapon::set_angle_change_direction(float direction) {
    m_current_angle_change_direction = direction;
}

void Weapon::set_currently_charging(bool is_charging) {
    m_is_charging = is_charging;
}

void Weapon::reset() {
    m_current_angle_change_direction = 0;
}
