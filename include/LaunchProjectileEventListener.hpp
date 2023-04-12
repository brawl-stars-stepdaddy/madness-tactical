#ifndef LAUNCH_PROJECTILE_EVENT_LISTENER_HPP_
#define LAUNCH_PROJECTILE_EVENT_LISTENER_HPP_

#include "EventListener.hpp"
#include "LaunchProjectileEventData.hpp"
#include "World.hpp"

struct LaunchProjectileEventListener : EventListener {
public:
    explicit LaunchProjectileEventListener(World *world);

    void process(const EventData &event) override;

private:
    World *m_world;
};

#endif // LAUNCH_PROJECTILE_EVENT_LISTENER_HPP_
