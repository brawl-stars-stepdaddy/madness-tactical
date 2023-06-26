#include "logic/states/PauseState.hpp"
#include "gui/Button.hpp"
#include "utils/GuiUtil.hpp"
#include "utils/ResourceHolder.hpp"
#include "utils/ResourceIdentifiers.hpp"

PauseState::PauseState(StateStack &stack, State::Context context)
    : State(stack, context),
      m_text_effect_time(sf::Time::Zero),
      m_show_text(true) {
    m_pause_text.setString("PAUSE");
    m_pause_text.setFont(context.fonts->get(FontsID::SANSATION));
    GuiUtil::center(m_pause_text);
    m_pause_text.setPosition(
        context.window->getView().getCenter() + sf::Vector2f(0, -300)
    );
    auto resume_button = std::make_unique<GUI::Button>(*context.fonts);
    resume_button->setPosition(context.window->getView().getSize() / 2.f);
    resume_button->set_text("Resume");
    resume_button->set_callback([this]() { request_stack_pop(); });
    m_gui_container.pack(std::move(resume_button));

    auto exit_button = std::make_unique<GUI::Button>(*context.fonts);
    exit_button->setPosition(
        context.window->getView().getSize() / 2.f + sf::Vector2f(0, 100)
    );
    exit_button->set_text("Exit to menu");
    exit_button->set_callback([this]() {
        request_stack_clear();
        request_stack_push(StatesID::Menu);
    });
    m_gui_container.pack(std::move(exit_button));
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
    get_context().window->draw(m_gui_container);
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
    m_gui_container.handle_input(event);
    return false;
}

bool PauseState::handle_realtime_input() {
    return false;
}
