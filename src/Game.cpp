#include "Game.hpp"
#include <cmath>

Game::Game() :
m_window(sf::VideoMode(1080, 1080), "SFML test"),
m_player(),
m_texture(),
m_player_speed(500.f) {
    m_resource_holder.load(TexturesID::SUN, "../res/The_Sun_in_high_resolution_pillars.jpg");
    m_resource_holder.load(TexturesID::DIRT, "../res/dirt.jpg");
    m_resource_holder.get(TexturesID::DIRT).setRepeated(true);
    m_resource_holder.get(TexturesID::DIRT).setSmooth(true);
    shape1.setPointCount(3);
    shape1.setPoint(0, {0, 0});
    shape1.setPoint(1, {300, 300});
    shape1.setPoint(2, {50, 400});
    shape2.setPointCount(3);
    shape2.setPoint(0, {300 - 300, 300 - 300});
    shape2.setPoint(1, {50 - 300, 400 - 300});
    shape2.setPoint(2, {500 - 300, 350 - 300});
    shape2.setPosition({300, 300});
    shape1.setTextureRect(sf::IntRect(0, 0, 300, 400));
    shape1.setTexture(&m_resource_holder.get(TexturesID::DIRT));
    shape2.setTextureRect(sf::IntRect(50, 300, 450, 100));
    shape2.setTexture(&m_resource_holder.get(TexturesID::DIRT));
    m_player.setTexture(m_resource_holder.get(TexturesID::DIRT));
    m_player.setPosition(200.f, 200.f);
    sf::FloatRect bounds = m_player.getLocalBounds();
    m_player.setOrigin(bounds.width / 2.f, bounds.height / 2.f);
}

void Game::run() {
    sf::Clock clock;
    sf::Time unprocessed = sf::Time::Zero;
    sf::Time time_per_frame = sf::seconds(1.f / 60);
    while (m_window.isOpen()) {
        unprocessed += clock.restart();
        process_events();
        while (unprocessed >= time_per_frame) {
            unprocessed -= time_per_frame;
            update(time_per_frame);
        }
        render();
    }
}

void Game::handle_player_input(sf::Keyboard::Key key, bool is_pressed) {
    if (key == sf::Keyboard::Key::W) {
        m_is_moving_up = is_pressed;
    } else if (key == sf::Keyboard::Key::S) {
        m_is_moving_down = is_pressed;
    } else if (key == sf::Keyboard::Key::A) {
        m_is_moving_left = is_pressed;
    } else if (key == sf::Keyboard::Key::D) {
        m_is_moving_right = is_pressed;
    }
}

void Game::process_events() {
    sf::Event event;
    while (m_window.pollEvent(event)) {
        switch (event.type) {
            case sf::Event::Closed:
                m_window.close();
                break;
            case sf::Event::KeyPressed:
                handle_player_input(event.key.code, true);
                break;
            case sf::Event::KeyReleased:
                handle_player_input(event.key.code, false);
                break;
            default:
                break;
        }
    }
}

void Game::update(sf::Time delta_time) {
    sf::Vector2f movement(0.f, 0.f);
    if (m_is_moving_up) {
        movement.y -= 1.f;
    }
    if (m_is_moving_down) {
        movement.y += 1.f;
    }
    if (m_is_moving_left) {
        movement.x -= 1.f;
    }
    if (m_is_moving_right) {
        movement.x += 1.f;
    }
    m_player.rotate(delta_time.asSeconds());
    m_player.move(movement * m_player_speed * delta_time.asSeconds());
}

void Game::render() {
    m_window.clear();
    m_window.draw(shape1);
    m_window.draw(shape2);
    m_window.draw(m_player);
    m_window.display();
}
