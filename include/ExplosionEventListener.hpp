#ifndef EXPLOSION_EVENT_LISTENER_HPP
#define EXPLOSION_EVENT_LISTENER_HPP

#include "EventListener.hpp"
#include "ExplosionEventData.hpp"
#include "World.hpp"

struct ExplosionEventListener : EventListener {
public:
    ExplosionEventListener(World *world);

    void process(const EventData &event) override;

private:
    World *m_world;
};

#endif
