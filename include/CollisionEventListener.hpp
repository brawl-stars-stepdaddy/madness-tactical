#ifndef COLLISION_EVENT_LISTENER_HPP_
#define COLLISION_EVENT_LISTENER_HPP_

#include "EventListener.hpp"
#include "CollisionEventData.hpp"
#include "World.hpp"

struct CollisionEventListener : EventListener {
public:
    void process(const EventData &event) override;
};

#endif // COLLISION_EVENT_LISTENER_HPP_
