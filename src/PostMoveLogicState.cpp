#include "PostMoveLogicState.hpp"
#include "PostMoveController.hpp"
#include "Weapon.hpp"

PostMoveLogicState::PostMoveLogicState(StateStack &stack, State::Context context, GameState &game_state)
    :   State(stack, context), m_game_state(&game_state) {
    m_controller = std::make_unique<PostMoveController>(game_state);
    auto camera = m_game_state->get_world()->get_camera();
    auto target = std::static_pointer_cast<Unit>(m_game_state->get_team_manager()->get_active_team()->get_active_unit()->get_pointer());
    camera->set_follow_strategy(std::make_unique<SmoothFollowStrategy>(camera, target));
}

void PostMoveLogicState::draw() {}

bool PostMoveLogicState::update(sf::Time delta_time) {
    m_timer -= delta_time;
    if (m_timer <= sf::Time::Zero) {
        request_stack_clear();
        request_stack_push(StatesID::BloodyFatality);
    }
    return false;
}

bool PostMoveLogicState::handle_input(const sf::Event &event) {
    m_controller->handle_input(event);
    return false;
}

bool PostMoveLogicState::handle_realtime_input() {
    m_controller->handle_realtime_input();
    return false;
}

