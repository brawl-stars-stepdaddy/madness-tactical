#ifndef EXPLOSION_EVENT_DATA_HPP
#define EXPLOSION_EVENT_DATA_HPP

#include "EventData.hpp"
#include "Explosion.hpp"

struct ExplosionEventData : EventData {
public:
    explicit ExplosionEventData(Explosion explosion);

    [[nodiscard]] EventType get_event_type() const override {
        return EventType::EXPLOSION;
    }

    [[nodiscard]] Explosion get_explosion() const {
        return m_explosion;
    }

private:
    Explosion m_explosion;
};

#endif
