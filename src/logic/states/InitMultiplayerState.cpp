#include "logic/states/InitMultiplayerState.hpp"
#include "utils/GuiUtil.hpp"
#include "utils/ResourceHolder.hpp"
#include "utils/ResourceIdentifiers.hpp"

InitMultiplayerState::InitMultiplayerState(StateStack &stack, State::Context context) : State(stack, context) {
    m_text.setString("Waiting for second localhost player");
    m_text.setFont(get_context().fonts->get(FontsID::SANSATION));
    GuiUtil::center(m_text);
    m_text.setPosition(get_context().window->getDefaultView().getCenter());
    m_background.setTexture(get_context().textures->get(TexturesID::BACKGROUND));
    m_game_client = std::make_unique<GameClient>();
    m_game_client->start_client();
}

void InitMultiplayerState::draw() {
    get_context().window->setView(get_context().window->getDefaultView());
    get_context().window->draw(m_background);
    get_context().window->draw(m_text);
}

bool InitMultiplayerState::update(sf::Time delta_time) {
    if (m_game_client->is_ready()) {
        m_text.setString("Connected " + std::to_string(m_game_client->get_number()));
        //request_stack_clear();
        //request_stack_push(StatesID::);
    }
    return false;
}

bool InitMultiplayerState::handle_input(const sf::Event &event) {
    if (event.type == sf::Event::KeyReleased && event.key.code == sf::Keyboard::Escape) {
        m_game_client->close();
        request_stack_pop();
        request_stack_push(StatesID::MENU);
    }
    return false;
}

bool InitMultiplayerState::handle_realtime_input() {
    return false;
}
