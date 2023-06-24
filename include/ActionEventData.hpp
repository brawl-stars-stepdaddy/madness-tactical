#ifndef ACTION_EVENT_DATA_HPP_
#define ACTION_EVENT_DATA_HPP_

#include "EventData.hpp"

struct ChangeAngleUpEventData : EventData {
public:
    [[nodiscard]] EventType get_event_type() const override {
        return EventType::CHANGE_ANGLE_UP;
    }
};

struct ChangeAngleDownEventData : EventData {
public:
    [[nodiscard]] EventType get_event_type() const override {
        return EventType::CHANGE_ANGLE_DOWN;
    }
};

struct MoveLeftEventData : EventData {
public:
    [[nodiscard]] EventType get_event_type() const override {
        return EventType::MOVE_LEFT;
    }
};

struct MoveRightEventData : EventData {
public:
    [[nodiscard]] EventType get_event_type() const override {
        return EventType::MOVE_RIGHT;
    }
};

struct JumpForwardEventData : EventData {
public:
    [[nodiscard]] EventType get_event_type() const override {
        return EventType::JUMP_FORWARD;
    }
};

struct JumpBackwardEventData : EventData {
public:
    [[nodiscard]] EventType get_event_type() const override {
        return EventType::JUMP_BACKWARD;
    }
};

struct BeginChargeWeaponEventData : EventData {
public:
    [[nodiscard]] EventType get_event_type() const override {
        return EventType::BEGIN_CHARGE_WEAPON;
    }
};

struct LaunchProjectileEventData : EventData {
public:
    [[nodiscard]] EventType get_event_type() const override {
        return EventType::LAUNCH_PROJECTILE;
    }
};

struct ZoomInEventData : EventData {
public:
    [[nodiscard]] EventType get_event_type() const override {
        return EventType::ZOOM_IN;
    }
};

struct ZoomOutEventData : EventData {
public:
    [[nodiscard]] EventType get_event_type() const override {
        return EventType::ZOOM_OUT;
    }
};

struct CameraMoveLeftEventData : EventData {
public:
    [[nodiscard]] EventType get_event_type() const override {
        return EventType::CAMERA_MOVE_LEFT;
    }
};

struct CameraMoveRightEventData : EventData {
public:
    [[nodiscard]] EventType get_event_type() const override {
        return EventType::CAMERA_MOVE_RIGHT;
    }
};


struct CameraMoveUpEventData : EventData {
public:
    [[nodiscard]] EventType get_event_type() const override {
        return EventType::CAMERA_MOVE_UP;
    }
};


struct CameraMoveDownEventData : EventData {
public:
    [[nodiscard]] EventType get_event_type() const override {
        return EventType::CAMERA_MOVE_DOWN;
    }
};

#endif  // ACTION_EVENT_DATA_HPP_
