#ifndef COLLISION_EVENT_LISTENER_HPP_
#define COLLISION_EVENT_LISTENER_HPP_

#include <set>
#include "EventListener.hpp"
#include "CollisionEventData.hpp"
#include "ContactListener.hpp"
#include "World.hpp"

struct CollisionEventListener : EventListener {
public:
    explicit CollisionEventListener(World *);
    void process(const EventData &event) override;
    void reset();

private:
    ContactListener m_contact_listener;
    std::set<std::pair<Entity *, Entity *>> processed_collisions;
};

#endif // COLLISION_EVENT_LISTENER_HPP_
