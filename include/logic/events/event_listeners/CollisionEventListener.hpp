#ifndef COLLISION_EVENT_LISTENER_HPP_
#define COLLISION_EVENT_LISTENER_HPP_

#include <set>
#include "EventListener.hpp"
#include "logic/events/event_data/CollisionEventData.hpp"
#include "utils/ContactListener.hpp"

struct World;

struct CollisionEventListener : EventListener {
public:
    explicit CollisionEventListener(World &world);

    void process(const EventData &event) override;
    void reset();

private:
    World *m_world;
    ContactListener m_contact_listener;
    std::set<std::pair<std::shared_ptr<Entity>, std::shared_ptr<Entity>>> processed_collisions;
};

#endif  // COLLISION_EVENT_LISTENER_HPP_
