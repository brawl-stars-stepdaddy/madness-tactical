#include "ActionEventListener.hpp"
#include "ActionEventData.hpp"
#include "Camera.hpp"
#include "ChargeableWeapon.hpp"
#include "GameLogic.hpp"
#include "Unit.hpp"
#include "World.hpp"

ZoomInEventListener::ZoomInEventListener(Camera *camera) : m_camera(camera) {
}

ZoomOutEventListener::ZoomOutEventListener(Camera *camera) : m_camera(camera) {
}

void ChangeAngleDownEventListener::process(const EventData &event) {
    auto weapon = static_cast<RotatableWeapon *>(
        m_game_logic->get_current_unit()->get_weapon()
    );
    weapon->set_angle_change_direction(-1);
}

ChangeAngleDownEventListener::ChangeAngleDownEventListener(
    World &world,
    GameLogic &game_logic
)
    : ActionEventListener(world, game_logic) {
}

void ChangeAngleUpEventListener::process(const EventData &event) {
    auto weapon = static_cast<RotatableWeapon *>(
        m_game_logic->get_current_unit()->get_weapon()
    );
    weapon->set_angle_change_direction(1);
}

ChangeAngleUpEventListener::ChangeAngleUpEventListener(
    World &world,
    GameLogic &game_logic
)
    : ActionEventListener(world, game_logic) {
}

void MoveLeftEventListener::process([[maybe_unused]] const EventData &event) {
    m_game_logic->get_current_unit()->set_dumping_active(true);
    m_game_logic->get_current_unit()->set_moving_active(true);
    m_game_logic->get_current_unit()->set_direction(-1);
}

MoveLeftEventListener::MoveLeftEventListener(
    World &world,
    GameLogic &game_logic
)
    : ActionEventListener(world, game_logic) {
}

void MoveRightEventListener::process([[maybe_unused]] const EventData &event) {
    m_game_logic->get_current_unit()->set_dumping_active(true);
    m_game_logic->get_current_unit()->set_moving_active(true);
    m_game_logic->get_current_unit()->set_direction(1);
}

MoveRightEventListener::MoveRightEventListener(
    World &world,
    GameLogic &game_logic
)
    : ActionEventListener(world, game_logic) {
}

void JumpForwardEventListener::process([[maybe_unused]] const EventData &event
) {
    m_game_logic->get_current_unit()->jump_forward();
}

JumpForwardEventListener::JumpForwardEventListener(
    World &world,
    GameLogic &game_logic
)
    : ActionEventListener(world, game_logic) {
}

void JumpBackwardEventListener::process([[maybe_unused]] const EventData &event
) {
    m_game_logic->get_current_unit()->jump_backward();
}

JumpBackwardEventListener::JumpBackwardEventListener(
    World &world,
    GameLogic &game_logic
)
    : ActionEventListener(world, game_logic) {
}

void BeginChargeWeaponEventListener::process(const EventData &event) {
    auto weapon = static_cast<ChargeableWeapon *>(
        m_game_logic->get_current_unit()->get_weapon()
    );
    weapon->set_currently_charging(true);
}

BeginChargeWeaponEventListener::BeginChargeWeaponEventListener(
    World &world,
    GameLogic &game_logic
)
    : ActionEventListener(world, game_logic) {
}

void LaunchProjectileEventListener::process(const EventData &event) {
    assert(event.get_event_type() == EventType::LAUNCH_PROJECTILE);
    auto launch_event = static_cast<const LaunchProjectileEventData &>(event);
    m_game_logic->get_current_unit()->get_weapon()->launch();
}

LaunchProjectileEventListener::LaunchProjectileEventListener(
    World &world,
    GameLogic &game_logic
)
    : ActionEventListener(world, game_logic) {
}

void ZoomInEventListener::process([[maybe_unused]] const EventData &event) {
    m_camera->zoom_in();
}

void ZoomOutEventListener::process([[maybe_unused]] const EventData &event) {
    m_camera->zoom_out();
}

ActionEventListener::ActionEventListener(World &world, GameLogic &game_logic)
    : m_world(&world), m_game_logic(&game_logic) {
}

CameraMoveLeftEventListener::CameraMoveLeftEventListener(Camera *camera) : m_camera(camera) {

}

void CameraMoveLeftEventListener::process(const EventData &event) {
    m_camera->move_left();
}

CameraMoveRightEventListener::CameraMoveRightEventListener(Camera *camera) : m_camera(camera) {

}

void CameraMoveRightEventListener::process(const EventData &event) {
    m_camera->move_right();
}

CameraMoveUpEventListener::CameraMoveUpEventListener(Camera *camera) : m_camera(camera) {

}

void CameraMoveUpEventListener::process(const EventData &event) {
    m_camera->move_up();
}

CameraMoveDownEventListener::CameraMoveDownEventListener(Camera *camera) : m_camera(camera) {

}

void CameraMoveDownEventListener::process(const EventData &event) {
    m_camera->move_down();
}
