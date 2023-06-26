#include "InitLogicState.hpp"
#include "InitController.hpp"

InitLogicState::InitLogicState(StateStack &stack, State::Context context, GameState &game_state) : State(stack, context), m_game_state(&game_state) {
    m_controller = std::make_unique<InitController>(game_state);
    auto camera = m_game_state->get_world()->get_camera();
    camera->set_follow_strategy(std::make_unique<ControlledFollowStrategy>(camera));

    for (int i = 0; i < m_team_number; i++) {
        m_game_state->get_team_manager()->create_team(m_colors[i]);
    }
}

void InitLogicState::draw() {}

bool InitLogicState::update(sf::Time delta_time) {
    if (m_game_state->get_team_manager()->get_number_available_units() >= m_team_number * m_team_size) {
        request_stack_clear();
        request_stack_push(StatesID::Move);
    }
    return false;
}

bool InitLogicState::handle_input(const sf::Event &event) {
    m_controller->handle_input(event);
    return false;
}

bool InitLogicState::handle_realtime_input() {
    m_controller->handle_realtime_input();
    return false;
}
