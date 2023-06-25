#include "TitleState.hpp"
#include "GuiUtil.hpp"
#include "ResourceHolder.hpp"
#include <iostream>

TitleState::TitleState(StateStack &stack, State::Context context)
    : State(stack, context) {
    m_brawl_start_stepdaddy_texture.loadFromFile("res/brawl_stars_stepdaddy.png");
    m_in_association_with_texture.loadFromFile("res/in_association_with.png");
    m_presents_texture.loadFromFile("res/presents.png");

    m_brawl_start_stepdaddy_sprite.setTexture(m_brawl_start_stepdaddy_texture);
    m_in_association_with_sprite.setTexture(m_in_association_with_texture);
    m_presents_sprite.setTexture(m_presents_texture);

    GuiUtil::center(m_brawl_start_stepdaddy_sprite);
    GuiUtil::center(m_in_association_with_sprite);
    GuiUtil::center(m_presents_sprite);

    m_brawl_start_stepdaddy_sprite.setPosition(get_context().window->getView().getSize() / 2.f - sf::Vector2f(0, m_brawl_start_stepdaddy_sprite.getLocalBounds().height / 2 + 20));
    m_in_association_with_sprite.setPosition(get_context().window->getView().getSize() / 2.f + sf::Vector2f(0, m_in_association_with_sprite.getLocalBounds().height / 2 + 20));
    m_presents_sprite.setPosition(get_context().window->getView().getSize() / 2.f);
}

void TitleState::draw() {
    get_context().window->setView(get_context().window->getDefaultView());
    if (m_current_time <= m_show_text_time * 2.f + sf::seconds(0.5)) {
        sf::RectangleShape fade1;
        fade1.setSize({m_brawl_start_stepdaddy_sprite.getLocalBounds().width, m_brawl_start_stepdaddy_sprite.getLocalBounds().height});
        GuiUtil::center(fade1);
        fade1.setPosition(m_brawl_start_stepdaddy_sprite.getPosition());

        sf::RectangleShape fade2;
        fade2.setSize({m_in_association_with_sprite.getLocalBounds().width, m_in_association_with_sprite.getLocalBounds().height});
        GuiUtil::center(fade2);
        fade2.setPosition(m_in_association_with_sprite.getPosition());

        fade1.setFillColor(sf::Color(0, 0, 0, sf::Uint8(255 - std::min(255.f, m_current_time * 255.f / m_show_text_time))));
        fade2.setFillColor(sf::Color(0, 0, 0, sf::Uint8(255 - std::min(255.f, std::max(0.f, (m_current_time - m_show_text_time) * 255.f / m_show_text_time)))));

        get_context().window->draw(m_brawl_start_stepdaddy_sprite);
        get_context().window->draw(m_in_association_with_sprite);
        get_context().window->draw(fade1);
        get_context().window->draw(fade2);
    } else if (m_current_time <= m_show_text_time * 2.f + m_time_per_logo * static_cast<float>(m_n_logos) + sf::seconds(0.5)) {
        sf::Time t1 = m_current_time - m_show_text_time * 2.f - sf::seconds(0.5);
        int n_logo = 1;
        while (t1 - m_time_per_logo >= sf::Time::Zero) {
            t1 -= m_time_per_logo;
            n_logo++;
        }
        if (n_logo != m_cur_logo) {
            m_cur_logo = n_logo;
            m_logo_texture.loadFromFile("res/logos/" + std::to_string(n_logo) + ".png");
            m_logo_sprite.setTexture(m_logo_texture, true);
            GuiUtil::resize(m_logo_sprite, sf::Vector2u(get_context().window->getView().getSize()));
        }
        sf::RectangleShape fade;
        fade.setSize({static_cast<float>(get_context().window->getSize().x), static_cast<float>(get_context().window->getSize().y)});
        fade.setFillColor(sf::Color(0, 0, 0, sf::Uint8((m_time_per_logo - t1) * 255.f / m_time_per_logo)));
        get_context().window->draw(m_logo_sprite);
        get_context().window->draw(fade);
    } else if (m_current_time <= m_show_text_time * 2.f + m_time_per_logo * static_cast<float>(m_n_logos) + sf::seconds(1)) {
        sf::Time t1 = m_current_time - (m_show_text_time * 2.f + m_time_per_logo * static_cast<float>(m_n_logos) + sf::seconds(0.5));
        sf::RectangleShape fade;
        fade.setSize({static_cast<float>(get_context().window->getSize().x), static_cast<float>(get_context().window->getSize().y)});
        fade.setFillColor(sf::Color(0, 0, 0, sf::Uint8(std::min(255.f, 255 - (m_time_per_logo - t1) * 255.f / m_time_per_logo))));
        get_context().window->draw(m_logo_sprite);
        get_context().window->draw(fade);
    } else {
        sf::RectangleShape fade;
        fade.setSize({m_presents_sprite.getLocalBounds().width, m_presents_sprite.getLocalBounds().height});
        GuiUtil::center(fade);
        fade.setPosition(m_presents_sprite.getPosition());

        fade.setFillColor(sf::Color(0, 0, 0, sf::Uint8(std::min(255.f, std::abs((m_current_time - (m_show_text_time * 3.f + m_time_per_logo * static_cast<float>(m_n_logos) + sf::seconds(1))) * 255.f / m_show_text_time)))));

        get_context().window->draw(m_presents_sprite);
        get_context().window->draw(fade);
    }
}

bool TitleState::update(sf::Time delta_time) {
    m_current_time += delta_time;
    if (m_current_time >= m_total_title_time) {
        request_stack_pop();
        request_stack_push(StatesID::Menu);
    }
    return false;
}

bool TitleState::handle_input(const sf::Event &event) {
    if (event.type == sf::Event::KeyReleased) {
        request_stack_pop();
        request_stack_push(StatesID::Menu);
    }
    return false;
}

bool TitleState::handle_realtime_input() {
    return false;
}
