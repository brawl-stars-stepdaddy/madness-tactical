#include "logic/states/logic_states/InitLogicState.hpp"
#include "logic/controllers/InitController.hpp"
#include "utils/ResourceHolder.hpp"
#include "utils/GuiUtil.hpp"

InitLogicState::InitLogicState(
    StateStack &stack,
    State::Context context,
    GameState &game_state
)
    : State(stack, context), m_game_state(&game_state) {
    m_controller = std::make_unique<InitController>(game_state);
    auto camera = m_game_state->get_world()->get_camera();
    camera->set_follow_strategy(
        std::make_unique<ControlledFollowStrategy>(camera)
    );

    for (int i = 0; i < m_team_number; i++) {
        m_game_state->get_team_manager()->create_team(m_colors[i]);
    }
}

void InitLogicState::draw() {
    get_context().window->setView(get_context().window->getDefaultView());
    sf::Sprite aim;
    aim.setTexture(get_context().textures->get(TexturesID::AIM));
    GuiUtil::center(aim);
    GuiUtil::resize(aim, {100, 100});
    aim.setPosition(get_context().window->getView().getCenter());
    get_context().window->draw(aim);
}

bool InitLogicState::update(sf::Time delta_time) {
    if (m_game_state->get_team_manager()->get_number_available_units() >=
        m_team_number * m_team_size) {
        request_stack_clear();
        request_stack_push(StatesID::MOVE);
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
