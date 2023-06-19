#include "GameState.hpp"

GameState::GameState(StateStack &stack, State::Context context)
    : State(stack, context),
      m_controller(*this),
      m_world(context, m_event_manager) {
}

void GameState::draw() {
    m_world.draw();
}

bool GameState::update(sf::Time delta_time) {
    m_world.update(delta_time);
    m_event_manager.update();
    return false;
}

bool GameState::handle_input(const sf::Event &event) {
    if (event.type == sf::Event::KeyReleased &&
        event.key.code == sf::Keyboard::Escape) {
        request_stack_push(StatesID::Pause);
    }
    m_controller.handle_input(event);
    return false;
}

bool GameState::handle_realtime_input() {
    m_controller.handle_realtime_input();
    return false;
}

EventManager *GameState::get_event_manager() {
    return &m_event_manager;
}
