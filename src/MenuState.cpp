#include "MenuState.hpp"
#include "Button.hpp"
#include "GuiUtil.hpp"
#include "ResourceHolder.hpp"

MenuState::MenuState(StateStack &stack, State::Context context)
    : State(stack, context), m_gui_container(), m_event_manager(), m_background_world(context, m_event_manager) {
    m_background_world.build_start_scene();
    auto play_button = std::make_unique<GUI::Button>(*context.fonts);
    play_button->setPosition(context.window->getView().getSize() / 2.f);
    play_button->set_text("Play");
    play_button->set_callback([this]() {
        request_stack_pop();
        request_stack_push(StatesID::Game);
    });
    m_gui_container.pack(std::move(play_button));

    auto exit_button = std::make_unique<GUI::Button>(*context.fonts);
    exit_button->setPosition(
        context.window->getView().getSize() / 2.f + sf::Vector2f(0, 100)
    );
    exit_button->set_text("Exit");
    exit_button->set_callback([this]() { request_stack_pop(); });
    m_gui_container.pack(std::move(exit_button));
}

void MenuState::draw() {
    // TODO: draw background
    m_background_world.draw();
    get_context().window->setView(get_context().window->getDefaultView());
    get_context().window->draw(m_gui_container);
}

bool MenuState::update(sf::Time delta_time) {
    m_background_world.update(delta_time);
    m_event_manager.update();
    return false;
}

bool MenuState::handle_input(const sf::Event &event) {
    m_gui_container.handle_input(event);
    return false;
}

bool MenuState::handle_realtime_input() {
    return false;
}
