#ifndef ARMAGEDDON_PROCESS_HPP_
#define ARMAGEDDON_PROCESS_HPP_

#include "Process.hpp"

struct World;

struct ArmageddonProcess : Process {
    explicit ArmageddonProcess(World *);
    bool update(sf::Time) override;

private:
    World *m_world;

    float m_end_timer = 5.0f;
    float m_default_launch_time = 0.2f;
    float m_launch_timer = m_default_launch_time;

    float m_start_distance = 150.0f;
    float m_start_impulse = 5000.0f;

    float m_projectile_radius = 5.0f;
    float m_explosion_radius = 10.0f;
};

#endif // ARMAGEDDON_PROCESS_HPP_
