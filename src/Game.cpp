#include "Game.hpp"
#include <cmath>

Game::Game()
    : m_window(sf::VideoMode(1920, 1080), "SFML test", sf::Style::Fullscreen), m_world(m_window) {
    m_window.setKeyRepeatEnabled(false);
    m_statistics_font.loadFromFile("res/Sansation.ttf");
    m_statistics_text.setFont(m_statistics_font);
    m_statistics_text.setPosition(5.f, 5.f);
    m_statistics_text.setCharacterSize(10);
}

void Game::run() {
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

void Game::process_input() {
    sf::Event event;
    while (m_window.pollEvent(event)) {
        m_controller.handle_event(event);
        switch (event.type) {
            case sf::Event::Closed:
                m_window.close();
                break;
            default:
                break;
        }
    }

    m_controller.handle_realtime_input();
}

void Game::update(sf::Time delta_time) {
    m_world.update(delta_time);
}

void Game::render() {
    m_window.clear();
    m_world.draw();

    m_window.setView(m_window.getDefaultView());
    m_window.draw(m_statistics_text);
    m_window.display();
}

void Game::update_statistics(sf::Time delta_time) {
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
