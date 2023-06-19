#include "MenuState.hpp"
#include "ResourceHolder.hpp"
#include "ResourceIdentifiers.hpp"
#include "GuiUtil.hpp"

MenuState::MenuState(StateStack &stack, State::Context context) : State(stack, context), m_option_index(0) {
    sf::Text play_button;
    play_button.setFont(get_context().fonts->get(FontsID::SANSATION));
    play_button.setString("Play");
    GuiUtil::center(play_button);
    play_button.setPosition(context.window->getView().getSize() / 2.f);
    m_options.push_back(play_button);

    sf::Text exit_button;
    exit_button.setFont(get_context().fonts->get(FontsID::SANSATION));
    exit_button.setString("Exit");
    GuiUtil::center(exit_button);
    exit_button.setPosition(context.window->getView().getSize() / 2.f + sf::Vector2f{0, 30});
    m_options.push_back(exit_button);

    sf::Text huexit_button;
    huexit_button.setFont(get_context().fonts->get(FontsID::SANSATION));
    huexit_button.setString("Huexit");
    GuiUtil::center(huexit_button);
    huexit_button.setPosition(context.window->getView().getSize() / 2.f + sf::Vector2f{0, 60});
    m_options.push_back(huexit_button);
}

void MenuState::draw() {
    get_context().window->setView(get_context().window->getDefaultView());
    for (auto &text : m_options) {
        get_context().window->draw(text);
    }
}

bool MenuState::update(sf::Time delta_time) {
    update_option_text();
    return false;
}

bool MenuState::handle_input(const sf::Event &event) {
    if (event.type == sf::Event::KeyReleased && event.key.code == sf::Keyboard::Up) {
        m_option_index = std::max(m_option_index - 1, 0);
    } else if (event.type == sf::Event::KeyReleased && event.key.code == sf::Keyboard::Down) {
        m_option_index = std::min(m_option_index + 1, static_cast<int>(NOptions) - 1);
    } else if (event.type == sf::Event::KeyReleased && event.key.code == sf::Keyboard::Enter) {
        if (m_option_index == 0) {
            request_stack_pop();
            request_stack_push(StatesID::Game);
        } else if (m_option_index == 1) {
            request_stack_pop();
        } else {
            m_options[Huexit].setString("Sam Sosi");
        }
    }
    return false;
}

bool MenuState::handle_realtime_input() {
    return false;
}

void MenuState::update_option_text() {
    if (m_options.empty()) {
        return;
    }
    for (auto &text : m_options) {
        text.setFillColor(sf::Color::White);
    }
    m_options[m_option_index].setFillColor(sf::Color::Red);
}
