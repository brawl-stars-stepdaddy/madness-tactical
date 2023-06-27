#ifndef LASER_HPP_
#define LASER_HPP_

#include "RotatableWeapon.hpp"

struct Laser : RotatableWeapon {
public:
    Laser(World &world, Unit *parent);

    void launch() override;

private:
    void update_current(sf::Time delta_time) override;
    void draw_current(sf::RenderTarget &target, sf::RenderStates states) const override;

    void create_new_explosion();

    sf::Vector2f m_start_position;
    sf::Vector2f m_direction;

    int m_frequency = 3;
    int m_current_frequency = 0;
    float m_default_active_time = 2.5f;
    float m_active_time = m_default_active_time;
    float m_ray_radius = 0.4f;
    int m_explosions_number = 0;
    bool m_is_active = false;
    float m_laser_angle;

    sf::Sprite m_sprite;
};

#endif  // LASER_HPP_
