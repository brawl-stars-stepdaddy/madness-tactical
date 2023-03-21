#ifndef GAME_HPP_
#define GAME_HPP_

#include <SFML/Graphics.hpp>
#include "ResourceHolder.hpp"
#include "ResourceIdentifiers.hpp"
#include "World.hpp"

struct Game {
public:
    Game();
    void run();

private:
    void process_events();
    void update(sf::Time delta_time);
    void render();
    void handle_player_input(sf::Keyboard::Key key, bool is_pressed);
    void update_statistics(sf::Time delta_time);

    sf::RenderWindow m_window;
    sf::Text m_statistics_text;
    sf::Font m_statistics_font;
    sf::Time m_statistics_update_time;
    int m_statistics_num_frames;
    World m_world;
};

#endif