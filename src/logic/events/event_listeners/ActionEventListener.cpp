#include "logic/events/event_listeners/ActionEventListener.hpp"
#include "game_objects/entities/Unit.hpp"
#include "game_objects/weapons/ChargeableWeapon.hpp"
#include "logic/World.hpp"
#include "logic/events/event_data/ActionEventData.hpp"

ZoomInEventListener::ZoomInEventListener(Camera *camera) : m_camera(camera) {}

ZoomOutEventListener::ZoomOutEventListener(Camera *camera) : m_camera(camera) {}

void ChangeAngleDownEventListener::process(const EventData &event) {
    auto weapon = dynamic_cast<RotatableWeapon *>(
        m_world->get_player()->get_weapon()
    );
    if (weapon) {
        weapon->set_angle_change_direction(-1);
    }
}

ChangeAngleDownEventListener::ChangeAngleDownEventListener(World &world) : ActionEventListener(world) {}

void ChangeAngleUpEventListener::process(const EventData &event) {
    auto weapon = dynamic_cast<RotatableWeapon *>(
            m_world->get_player()->get_weapon()
    );
    if (weapon) {
        weapon->set_angle_change_direction(1);
    }
}

ChangeAngleUpEventListener::ChangeAngleUpEventListener(World &world) : ActionEventListener(world) {}

void MoveLeftEventListener::process([[maybe_unused]] const EventData &event) {
    m_world->get_player()->set_dumping_active(true);
    m_world->get_player()->set_moving_active(true);
    m_world->get_player()->set_direction(-1);
}

MoveLeftEventListener::MoveLeftEventListener(World &world) : ActionEventListener(world) {}

void MoveRightEventListener::process([[maybe_unused]] const EventData &event) {
    m_world->get_player()->set_dumping_active(true);
    m_world->get_player()->set_moving_active(true);
    m_world->get_player()->set_direction(1);
}

MoveRightEventListener::MoveRightEventListener(World &world) : ActionEventListener(world) {}

void JumpForwardEventListener::process([[maybe_unused]] const EventData &event
) {
    m_world->get_player()->jump_forward();
}

JumpForwardEventListener::JumpForwardEventListener(World &world) : ActionEventListener(world) {}

void JumpBackwardEventListener::process([[maybe_unused]] const EventData &event
) {
    m_world->get_player()->jump_backward();
}

JumpBackwardEventListener::JumpBackwardEventListener(World &world) : ActionEventListener(world) {}

void BeginChargeWeaponEventListener::process(const EventData &event) {
    auto weapon = dynamic_cast<ChargeableWeapon *>(
        m_world->get_player()->get_weapon()
    );
    if (weapon) {
        weapon->set_currently_charging(true);
    }
}

BeginChargeWeaponEventListener::BeginChargeWeaponEventListener(World &world) : ActionEventListener(world) {}

void LaunchProjectileEventListener::process(const EventData &event) {
    assert(event.get_event_type() == EventType::LAUNCH_PROJECTILE);
    auto launch_event = dynamic_cast<const LaunchProjectileEventData &>(event);
    m_world->get_player()->get_weapon()->launch();
}

LaunchProjectileEventListener::LaunchProjectileEventListener(World &world) : ActionEventListener(world) {}

void ZoomInEventListener::process([[maybe_unused]] const EventData &event) {
    m_camera->zoom_in();
}

void ZoomOutEventListener::process([[maybe_unused]] const EventData &event) {
    m_camera->zoom_out();
}

ActionEventListener::ActionEventListener(World &world) : m_world(&world) {}

CameraMoveLeftEventListener::CameraMoveLeftEventListener(Camera *camera)
    : m_camera(camera) {
}

void CameraMoveLeftEventListener::process(const EventData &event) {
    m_camera->move_left();
}

CameraMoveRightEventListener::CameraMoveRightEventListener(Camera *camera)
    : m_camera(camera) {
}

void CameraMoveRightEventListener::process(const EventData &event) {
    m_camera->move_right();
}

CameraMoveUpEventListener::CameraMoveUpEventListener(Camera *camera)
    : m_camera(camera) {
}

void CameraMoveUpEventListener::process(const EventData &event) {
    m_camera->move_up();
}

CameraMoveDownEventListener::CameraMoveDownEventListener(Camera *camera)
    : m_camera(camera) {
}

void CameraMoveDownEventListener::process(const EventData &event) {
    m_camera->move_down();
}
