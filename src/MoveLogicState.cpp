#include "MoveLogicState.hpp"
#include "Weapon.hpp"
#include "GuiUtil.hpp"

MoveLogicState::MoveLogicState(StateStack &stack, State::Context context, GameState &game_state) : State(stack, context), m_game_state(&game_state) {
    m_game_state->get_world()->set_active_unit(m_game_state->get_team_manager()->get_active_team()->get_active_unit());
    if (m_game_state->get_team_manager()->get_active_team()->get_active_unit()->get_weapon()->get_controller_type() == LAUNCH) {
        m_controller = std::make_unique<LaunchWeaponController>(game_state);
        m_game_state->get_world()->get_camera()->set_follow_strategy(std::make_unique<SmoothFollowStrategy>(m_game_state->get_world()->get_camera(), m_game_state->get_team_manager()->get_active_team()->get_active_unit()));
    } else {
        m_controller = std::make_unique<DistantWeaponController>(game_state);
        m_game_state->get_world()->get_camera()->set_follow_strategy(std::make_unique<ControlledFollowStrategy>(m_game_state->get_world()->get_camera()));
    }
    m_timer_text.setFont(get_context().fonts->get(FontsID::SANSATION));
    m_timer_text.setOutlineThickness(3.f);
    m_timer_text.setOutlineColor(sf::Color::Black);
    m_timer_text.setFillColor(sf::Color::White);
    m_timer_text.setCharacterSize(80);
    m_timer_text.setPosition(get_context().window->getView().getSize().x / 2.f, m_timer_text.getCharacterSize());
}

void MoveLogicState::draw() {
    get_context().window->setView(get_context().window->getDefaultView());
    get_context().window->draw(m_timer_text);
}

bool MoveLogicState::update(sf::Time delta_time) {
    m_timer -= delta_time;
    m_timer_text.setString(std::to_string(static_cast<int>(m_timer.asSeconds())));
    GuiUtil::center(m_timer_text);
    if (m_timer <= sf::Time::Zero) {
        request_stack_clear();
        request_stack_push(StatesID::BloodyFatality);
    }
    return false;
}

bool MoveLogicState::handle_input(const sf::Event &event) {
    m_controller->handle_input(event);
    return false;
}

bool MoveLogicState::handle_realtime_input() {
    m_controller->handle_realtime_input();
    return false;
}
