#include "PauseState.hpp"
#include "ResourceIdentifiers.hpp"
#include "ResourceHolder.hpp"
#include "GuiUtil.hpp"

PauseState::PauseState(StateStack &stack, State::Context context) : State(stack, context), m_text_effect_time(sf::Time::Zero), m_show_text(true) {
    m_pause_text.setString("BPEMR COCATb XYN!!! (pereryv 10 minutes)");
    m_pause_text.setFont(context.fonts->get(FontsID::SANSATION));
    GuiUtil::center(m_pause_text);
    m_pause_text.setPosition(context.window->getView().getCenter());
}

void PauseState::draw() {
    get_context().window->setView(get_context().window->getDefaultView());
    sf::RectangleShape background;
    background.setFillColor(sf::Color(0, 0, 0, 150));
    background.setSize(sf::Vector2f(get_context().window->getSize()));
    get_context().window->draw(background);
    if (m_show_text) {
        get_context().window->draw(m_pause_text);
    }
}

bool PauseState::update(sf::Time delta_time) {
    m_text_effect_time += delta_time;
    if (m_text_effect_time >= sf::seconds(0.5f)) {
        m_show_text = !m_show_text;
        m_text_effect_time = sf::Time::Zero;
    }
    return false;
}

bool PauseState::handle_input(const sf::Event &event) {
    if (event.type == sf::Event::KeyReleased && event.key.code == sf::Keyboard::Escape) {
        request_stack_pop();
    }
    return false;
}

bool PauseState::handle_realtime_input() {
    return false;
}
