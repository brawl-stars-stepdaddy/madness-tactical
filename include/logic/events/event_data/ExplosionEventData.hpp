#ifndef EXPLOSION_EVENT_DATA_HPP_
#define EXPLOSION_EVENT_DATA_HPP_

#include "EventData.hpp"
#include "game_objects/entities/Entity.hpp"
#include "utils/Explosion.hpp"

struct ExplosionEventData : EventData {
public:
    explicit ExplosionEventData(
        Explosion explosion,
        std::shared_ptr<Entity> object
    );

    [[nodiscard]] EventType get_event_type() const override {
        return EventType::EXPLOSION;
    }

    [[nodiscard]] Explosion get_explosion() const {
        return m_explosion;
    }

    [[nodiscard]] std::shared_ptr<Entity> get_object() const {
        return m_object;
    }

private:
    Explosion m_explosion;
    std::shared_ptr<Entity> m_object;
};

#endif // EXPLOSION_EVENT_DATA_HPP_
