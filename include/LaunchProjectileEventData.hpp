#ifndef LAUNCH_PROJECTILE_EVENT_DATA_HPP_
#define LAUNCH_PROJECTILE_EVENT_DATA_HPP_


#include "EventData.hpp"
#include "Entity.hpp"

struct LaunchProjectileEventData : EventData {
public:
    [[nodiscard]] EventType get_event_type() const override;
};

#endif // LAUNCH_PROJECTILE_EVENT_DATA_HPP_
