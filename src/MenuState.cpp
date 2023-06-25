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
    get_context().textures->load(TexturesID::GAME_TITLE, "res/madness_tactical.png");
    m_game_title_sprite.setTexture(get_context().textures->get(TexturesID::GAME_TITLE));
    GuiUtil::center(m_game_title_sprite);
    m_game_title_sprite.setPosition(get_context().window->getView().getCenter().x, m_game_title_sprite.getLocalBounds().height);
}

void MenuState::draw() {
    // TODO: draw background
    m_background_world.draw();
    get_context().window->setView(get_context().window->getDefaultView());
    sf::IntRect old_game_title_sprite_rect = m_game_title_sprite.getTextureRect();
    sf::IntRect new_game_title_sprite_rect = old_game_title_sprite_rect;
    new_game_title_sprite_rect.width -= new_game_title_sprite_rect.width * pow(std::max(0.f, (3.f - m_current_time.asSeconds()) * 2.f), 5) / 25.f / 32.f;
    m_game_title_sprite.setTextureRect(new_game_title_sprite_rect);
    get_context().window->draw(m_game_title_sprite);
    get_context().window->draw(m_gui_container);
    m_game_title_sprite.setTextureRect(old_game_title_sprite_rect);
}

bool MenuState::update(sf::Time delta_time) {
    m_current_time += delta_time;
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
