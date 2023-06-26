#ifndef COLLISION_EVENT_DATA_HPP_
#define COLLISION_EVENT_DATA_HPP_

#include "Entity.hpp"
#include "EventData.hpp"

struct CollisionEventData : EventData {
public:
    enum class CollisionType { BEGIN_CONTACT, END_CONTACT };

    explicit CollisionEventData(std::shared_ptr<Entity>, std::shared_ptr<Entity>, CollisionType);

    [[nodiscard]] EventType get_event_type() const override;

    [[nodiscard]] CollisionType get_collision_type() const;

    [[nodiscard]] std::shared_ptr<Entity> get_first_object() const;
    [[nodiscard]] std::shared_ptr<Entity> get_second_object() const;

private:
    std::shared_ptr<Entity> m_first_object;
    std::shared_ptr<Entity> m_second_object;
    CollisionType m_collision_type;
};

#endif  // COLLISION_EVENT_DATA_HPP_