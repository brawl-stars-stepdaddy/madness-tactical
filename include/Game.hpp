#ifndef GAME_HPP_
#define GAME_HPP_

#include <SFML/Graphics.hpp>
#include "ResourceHolder.hpp"
#include "ResourceIdentifiers.hpp"

struct Game {
public:
    Game();

    void run();

private:
    void process_events();

    void update(sf::Time delta_time);

    void render();

    void handle_player_input(sf::Keyboard::Key key, bool is_pressed);

    sf::RenderWindow m_window, m_window2;
    sf::Sprite m_player;
    sf::ConvexShape shape1;
    sf::ConvexShape shape2;
    sf::Texture m_texture;
    TextureHolder m_resource_holder;
    float m_player_speed;
    bool m_is_moving_up = false;
    bool m_is_moving_down = false;
    bool m_is_moving_left = false;
    bool m_is_moving_right = false;
};

#endif