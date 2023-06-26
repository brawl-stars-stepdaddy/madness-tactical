#include "logic/states/logic_states/GameOverLogicState.hpp"
#include "game_objects/weapons/Weapon.hpp"
#include "utils/GuiUtil.hpp"

GameOverLogicState::GameOverLogicState(
    StateStack &stack,
    State::Context context,
    GameState &game_state
)
    : State(stack, context), m_game_state(&game_state) {
    if (game_state.get_team_manager()->get_number_available_teams() == 0) {
        m_endgame_text.setString("Draw!");
    } else {
        m_endgame_text.setString("Win!");
        m_endgame_text.setFillColor(
            game_state.get_team_manager()->get_active_team()->get_team_color()
        );
    }

    m_endgame_text.setFont(get_context().fonts->get(FontsID::BAGEL_FONT));
    m_endgame_text.setOutlineThickness(10.f);
    m_endgame_text.setOutlineColor(sf::Color::Black);
    m_endgame_text.setCharacterSize(300);

    GuiUtil::center(m_endgame_text);
    m_endgame_text.setPosition(
        get_context().window->getView().getSize().x / 2.f,
        get_context().window->getView().getSize().y / 2.f
    );
}

void GameOverLogicState::draw() {
    get_context().window->setView(get_context().window->getDefaultView());
    get_context().window->draw(m_endgame_text);
}

bool GameOverLogicState::update(sf::Time delta_time) {
    return false;
}

bool GameOverLogicState::handle_input(const sf::Event &event) {
    return false;
}

bool GameOverLogicState::handle_realtime_input() {
    return false;
}
