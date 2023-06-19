#include "Application.hpp"
#include "GameState.hpp"
#include "TitleState.hpp"
#include "MenuState.hpp"
#include "PauseState.hpp"

Application::Application()
    : m_window(sf::VideoMode(1920, 1080), "SFML test", sf::Style::Fullscreen), m_state_stack(State::Context(m_window, m_textures, m_font_holder)) {
    m_window.setKeyRepeatEnabled(false);
    m_statistics_font.loadFromFile("res/Sansation.ttf");
    m_statistics_text.setFont(m_statistics_font);
    m_statistics_text.setPosition(5.f, 5.f);
    m_statistics_text.setCharacterSize(10);
    register_states();
    m_font_holder.load(FontsID::SANSATION, "res/Sansation.ttf");
    m_font_holder.load(FontsID::BAGEL_FONT, "res/BagelFatOne-Regular.ttf");
}

void Application::register_states() {
    m_state_stack.register_state<TitleState>(StatesID::Title);
    m_state_stack.register_state<MenuState>(StatesID::Menu);
    m_state_stack.register_state<GameState>(StatesID::Game);
    m_state_stack.register_state<PauseState>(StatesID::Pause);
    m_state_stack.push_state(StatesID::Title);
}

void Application::run() {
    sf::Clock clock;
    sf::Time unprocessed = sf::Time::Zero;
    sf::Time time_per_frame = sf::seconds(1.f / 60);
    sf::Time prev_render = sf::Time::Zero;
    while (m_window.isOpen()) {
        sf::Time elapsed_time = clock.restart();
        unprocessed += elapsed_time;
        prev_render += elapsed_time;
        process_input();
        bool updated = false;
        while (unprocessed >= time_per_frame) {
            updated = true;
            unprocessed -= time_per_frame;
            update(time_per_frame);
        }
        if (updated) {
            update_statistics(prev_render);
            render();
            prev_render = sf::Time::Zero;
        }
    }
}

void Application::process_input() {
    sf::Event event;
    while (m_window.pollEvent(event)) {
        m_state_stack.handle_input(event);
        switch (event.type) {
            case sf::Event::Closed:
                m_window.close();
                break;
            default:
                break;
        }
    }
    m_state_stack.handle_realtime_input();
}

void Application::update(sf::Time delta_time) {
    m_state_stack.update(delta_time);
    if (m_state_stack.is_empty()) {
        m_window.close();
    }
}

void Application::render() {
    m_window.clear();
    m_state_stack.draw();

    m_window.setView(m_window.getDefaultView());
    m_window.draw(m_statistics_text);
    m_window.display();
}

void Application::update_statistics(sf::Time delta_time) {
    m_statistics_update_time += delta_time;
    m_statistics_num_frames += 1;
    if (m_statistics_update_time >= sf::seconds(1)) {
        m_statistics_text.setString(
            "Frames / Second = " + std::to_string(m_statistics_num_frames)
        );

        m_statistics_update_time -= sf::seconds(1.0f);
        m_statistics_num_frames = 0;
    }
}
