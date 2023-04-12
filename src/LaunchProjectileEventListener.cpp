#include "LaunchProjectileEventListener.hpp"
#include "Weapon.hpp"

LaunchProjectileEventListener::LaunchProjectileEventListener(World *world) : m_world(world) {}

void LaunchProjectileEventListener::process(const EventData &event) {
    assert(event.get_event_type() == EventType::LAUNCH_PROJECTILE);
    auto launch_event = static_cast<const LaunchProjectileEventData &>(event);
    auto projectile = m_world->get_player()->get_weapon()->launch(*m_world);
    m_world->get_layer(World::Layer::ENTITIES)->attach_child(std::move(projectile));
}
