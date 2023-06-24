#include "ArmageddonProcess.hpp"
#include "World.hpp"
#include "CollisionProjectile.hpp"
#include <random>
#include <cmath>

ArmageddonProcess::ArmageddonProcess(World *world) : m_world(world) {}

bool ArmageddonProcess::update(sf::Time delta_time) {
    m_end_timer -= delta_time.asSeconds();
    m_launch_timer -= delta_time.asSeconds();
    if (m_launch_timer <= 0) {

        std::uniform_real_distribution<> range(0, M_PI * 2);
        std::mt19937 rand_gen((std::random_device()()));
        float angle = range(rand_gen);
        float x_norm = cos(angle);
        float y_norm = sin(angle);

        sf::Vector2f start_position = {x_norm * m_start_distance, y_norm * m_start_distance};
        sf::Vector2f impulse = {-x_norm * m_start_impulse, -y_norm * m_start_impulse};
        m_world->get_layer(World::Layer::ENTITIES)
                ->attach_child(std::make_unique<CollisionProjectile>(
                        *m_world, start_position, impulse, m_projectile_radius,
                        m_explosion_radius, false, false, TexturesID::METEORITE
                ));

        m_launch_timer = m_default_launch_time;
    }
    return m_end_timer <= 0;
}
