#ifndef EXPLOSION_EVENT_DATA_HPP
#define EXPLOSION_EVENT_DATA_HPP

#include "Entity.hpp"
#include "EventData.hpp"
#include "Explosion.hpp"

struct ExplosionEventData : EventData {
public:
    explicit ExplosionEventData(Explosion explosion, Entity *object);

    [[nodiscard]] EventType get_event_type() const override {
        return EventType::EXPLOSION;
    }

    [[nodiscard]] Explosion get_explosion() const {
        return m_explosion;
    }

    [[nodiscard]] Entity *get_object() const {
        return m_object;
    }

private:
    Explosion m_explosion;
    Entity *m_object;
};

#endif
