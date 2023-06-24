#include "TitleState.hpp"
#include "GuiUtil.hpp"
#include "ResourceHolder.hpp"

TitleState::TitleState(StateStack &stack, State::Context context)
    : State(stack, context) {
    context.textures->load(TexturesID::TITLE, "res/pososi.jpg");
    m_background_sprite.setTexture(context.textures->get(TexturesID::TITLE));
    GuiUtil::resize(m_background_sprite, get_context().window->getSize());
}

void TitleState::draw() {
    get_context().window->setView(get_context().window->getDefaultView());
    sf::RectangleShape fade(
        {static_cast<float>(get_context().window->getSize().x),
         static_cast<float>(get_context().window->getSize().y)}
    );
    fade.setFillColor(sf::Color(
        0, 0, 0,
        sf::Uint8(
            std::min(255.f, std::max(0.f, m_time.asSeconds() - 2.f) * 255 / 3.f)
        )
    ));
    fade.setPosition(0, 0);
    // get_context().window->draw(m_background_sprite);
    get_context().window->draw(m_background_sprite);
    get_context().window->draw(fade);
}

bool TitleState::update(sf::Time delta_time) {
    m_time -= delta_time;
    if (m_time.asSeconds() <= 0) {
        request_stack_pop();
        request_stack_push(StatesID::Menu);
    }
    return false;
}

bool TitleState::handle_input(const sf::Event &event) {
    if (event.type == sf::Event::KeyReleased) {
        m_time = sf::Time::Zero;
    }
    return false;
}

bool TitleState::handle_realtime_input() {
    return false;
}
