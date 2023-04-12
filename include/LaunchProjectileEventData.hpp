#ifndef LAUNCH_PROJECTILE_EVENT_DATA_HPP_
#define LAUNCH_PROJECTILE_EVENT_DATA_HPP_

#include "Entity.hpp"
#include "EventData.hpp"

struct LaunchProjectileEventData : EventData {
public:
    [[nodiscard]] EventType get_event_type() const override;
};

#endif  // LAUNCH_PROJECTILE_EVENT_DATA_HPP_
