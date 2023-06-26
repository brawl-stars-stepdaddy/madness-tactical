#ifndef MADNESS_TACTICAL_TITLESTATE_HPP
#define MADNESS_TACTICAL_TITLESTATE_HPP

#include <SFML/Graphics.hpp>
#include "State.hpp"

struct TitleState : State {
public:
    TitleState(StateStack &stack, Context context);
    virtual void draw() override;
    virtual bool update(sf::Time delta_time) override;
    virtual bool handle_input(const sf::Event &event) override;
    virtual bool handle_realtime_input() override;

private:
    sf::Sprite m_logo_sprite;
    sf::Texture m_logo_texture;

    sf::Sprite m_brawl_start_stepdaddy_sprite;
    sf::Texture m_brawl_start_stepdaddy_texture;

    sf::Sprite m_in_association_with_sprite;
    sf::Texture m_in_association_with_texture;

    sf::Sprite m_presents_sprite;
    sf::Texture m_presents_texture;

    int m_n_logos = 20;
    int m_cur_logo = 0;
    sf::Time m_current_time = sf::Time::Zero;
    sf::Time m_show_text_time = sf::seconds(1.5);
    sf::Time m_time_per_logo = sf::seconds(.15f);
    sf::Time m_total_title_time = sf::seconds(
        m_show_text_time.asSeconds() * 4 +
        m_time_per_logo.asSeconds() * m_n_logos + 1.f
    );
    sf::Text m_brawl_stars_stepdaddy_text;
    sf::Text m_in_association_with_text;
    sf::Text m_presents;
};

#endif
