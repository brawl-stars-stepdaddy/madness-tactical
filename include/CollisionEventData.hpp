#ifndef COLLISION_EVENT_DATA_HPP_
#define COLLISION_EVENT_DATA_HPP_

#include "Entity.hpp"
#include "EventData.hpp"

struct CollisionEventData : EventData {
public:
    explicit CollisionEventData(Entity *, Entity *);

    [[nodiscard]] EventType get_event_type() const override;

    [[nodiscard]] Entity *get_first_object() const;
    [[nodiscard]] Entity *get_second_object() const;

private:
    Entity *m_first_object;
    Entity *m_second_object;
};

#endif  // COLLISION_EVENT_DATA_HPP_
