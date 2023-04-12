#ifndef EXPLOSION_EVENT_LISTENER_HPP_
#define EXPLOSION_EVENT_LISTENER_HPP_

#include "EventListener.hpp"
#include "ExplosionEventData.hpp"
#include "World.hpp"

struct ExplosionEventListener : EventListener {
public:
    void process(const EventData &event) override;
};

#endif  // EXPLOSION_EVENT_LISTENER_HPP_
