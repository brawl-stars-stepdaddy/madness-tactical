#include <cmath>
#include "game_objects/weapons/RotatableWeapon.hpp"
#include "game_objects/entities/Unit.hpp"
#include "logic/World.hpp"
#include "utils/ResourceHolder.hpp"
#include "utils/GuiUtil.hpp"

void RotatableWeapon::update_current(sf::Time delta_time) {
    change_angle(delta_time, m_current_angle_change_direction);
    reset();
}

void RotatableWeapon::draw_current(
    sf::RenderTarget &target,
    sf::RenderStates states
) const {
    float angle = m_angle;
    float dist = 400.f;
    sf::Sprite aim;
    aim.setTexture(m_world->get_texture_holder().get(TexturesID::AIM));
    GuiUtil::center(aim);
    GuiUtil::resize(aim, {100, 100});
    aim.setPosition(sf::Vector2f{cos(angle), sin(angle)} * dist);
    target.draw(aim, states);
}

void RotatableWeapon::set_angle_change_direction(float direction) {
    m_current_angle_change_direction = direction;
}

void RotatableWeapon::change_angle(sf::Time delta_time, float direction) {
    if (!m_is_rotation_blocked) {
        m_angle = std::min(
            M_PI_2f,
            std::max(
                -M_PI_2f, m_angle + delta_time.asSeconds() * 1.f * -direction
            )
        );
    }
}

void RotatableWeapon::reset() {
    m_current_angle_change_direction = 0;
}

RotatableWeapon::RotatableWeapon(World &world) : Weapon(world) {}

WeaponControllerType RotatableWeapon::get_controller_type() {
    return LAUNCH;
}
