#include "ActionEventListener.hpp"
#include "GameLogic.hpp"
#include "Weapon.hpp"
#include "ActionEventData.hpp"
#include "Unit.hpp"
#include "World.hpp"

ChangeAngleDownEventListener::ChangeAngleDownEventListener(GameLogic *game_logic) : m_game_logic(game_logic) {
}

ChangeAngleUpEventListener::ChangeAngleUpEventListener(GameLogic *game_logic) : m_game_logic(game_logic) {
}

MoveLeftEventListener::MoveLeftEventListener(GameLogic *game_logic) : m_game_logic(game_logic) {
}

MoveRightEventListener::MoveRightEventListener(GameLogic *game_logic) : m_game_logic(game_logic) {
}

JumpForwardEventListener::JumpForwardEventListener(GameLogic *game_logic) : m_game_logic(game_logic) {
}

JumpBackwardEventListener::JumpBackwardEventListener(GameLogic *game_logic) : m_game_logic(game_logic) {
}

BeginChargeWeaponEventListener::BeginChargeWeaponEventListener(GameLogic *game_logic) : m_game_logic(game_logic) {
}

LaunchProjectileEventListener::LaunchProjectileEventListener(GameLogic *game_logic) : m_game_logic(game_logic) {
}

void ChangeAngleDownEventListener::process(const EventData &event) {
    m_game_logic->get_current_unit()->get_weapon()->set_angle_change_direction(-1);
}

void ChangeAngleUpEventListener::process(const EventData &event) {
    m_game_logic->get_current_unit()->get_weapon()->set_angle_change_direction(1);
}

void MoveLeftEventListener::process(const EventData &event) {
    m_game_logic->get_current_unit()->set_is_moving(true);
    m_game_logic->get_current_unit()->set_direction(-1);
}

void MoveRightEventListener::process(const EventData &event) {
    m_game_logic->get_current_unit()->set_is_moving(true);
    m_game_logic->get_current_unit()->set_direction(1);
}

void JumpForwardEventListener::process(const EventData &event) {
    m_game_logic->get_current_unit()->jump_forward();
}

void JumpBackwardEventListener::process(const EventData &event) {
    m_game_logic->get_current_unit()->jump_backward();
}

void BeginChargeWeaponEventListener::process(const EventData &event) {
    m_game_logic->get_current_unit()->get_weapon()->set_currently_charging(true);
}

void LaunchProjectileEventListener::process(const EventData &event) {
    assert(event.get_event_type() == EventType::LAUNCH_PROJECTILE);
    auto launch_event = static_cast<const LaunchProjectileEventData &>(event);
    m_game_logic->get_current_unit()->get_weapon()->launch(*m_game_logic->get_world());
}
