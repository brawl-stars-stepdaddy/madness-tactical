#include "logic/states/logic_states/BloodyFatalityLogicState.hpp"
#include "game_objects/weapons/Weapon.hpp"
#include "logic/controllers/CameraController.hpp"

BloodyFatalityLogicState::BloodyFatalityLogicState(
    StateStack &stack,
    State::Context context,
    GameState &game_state
)
    : State(stack, context), m_game_state(&game_state) {
    m_controller = std::make_unique<CameraController>(game_state);
    auto camera = m_game_state->get_world()->get_camera();
    auto bloody_fatality_candidates =
        m_game_state->get_world()->get_bloody_fatality_candidates();
    for (auto unit : bloody_fatality_candidates) {
        unit->kill_unit();
    }
    m_game_state->get_world()->reset_bloody_fatality_candidates();
    camera->set_follow_strategy(
        std::make_unique<ControlledFollowStrategy>(camera)
    );
}

void BloodyFatalityLogicState::draw() {
}

bool BloodyFatalityLogicState::update(sf::Time delta_time) {
    m_timer -= delta_time;
    if (m_timer <= sf::Time::Zero) {
        request_stack_clear();
        request_stack_push(StatesID::MoveTransition);
    }
    return false;
}

bool BloodyFatalityLogicState::handle_input(const sf::Event &event) {
    m_controller->handle_input(event);
    return false;
}

bool BloodyFatalityLogicState::handle_realtime_input() {
    m_controller->handle_realtime_input();
    return false;
}
