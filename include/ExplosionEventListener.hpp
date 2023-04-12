#ifndef EXPLOSION_EVENT_LISTENER_HPP_
#define EXPLOSION_EVENT_LISTENER_HPP_

#include "EventListener.hpp"
#include "ExplosionEventData.hpp"
#include "World.hpp"

struct ExplosionEventListener : EventListener {
public:
    explicit ExplosionEventListener(World *world);

    void process(const EventData &event) override;

private:
    World *m_world;
};

#endif  // EXPLOSION_EVENT_LISTENER_HPP_
