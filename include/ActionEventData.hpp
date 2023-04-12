#ifndef MADNESS_TACTICAL_ACTIONEVENTDATA_HPP
#define MADNESS_TACTICAL_ACTIONEVENTDATA_HPP

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

struct ChargeWeaponEventData : EventData {
public:
    [[nodiscard]] EventType get_event_type() const override {
        return EventType::CHARGE_WEAPON;
    }
};

struct LaunchProjectileEventData : EventData {
public:
    [[nodiscard]] EventType get_event_type() const override {
        return EventType::LAUNCH_PROJECTILE;
    }
};

#endif //MADNESS_TACTICAL_ACTIONEVENTDATA_HPP
