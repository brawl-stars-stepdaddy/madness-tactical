#ifndef GAME_HPP_
#define GAME_HPP_

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "Controller.hpp"
#include "GameLogic.hpp"
#include "ResourceHolder.hpp"
#include "ResourceIdentifiers.hpp"
#include "StateStack.hpp"
#include "World.hpp"

struct Application {
public:
    Application();
    void run();

private:
    void register_states();
    void process_input();
    void update(sf::Time delta_time);
    void render();
    void update_statistics(sf::Time delta_time);

    sf::RenderWindow m_window;
    sf::Text m_statistics_text;
    sf::Font m_statistics_font;
    sf::Time m_statistics_update_time;
    int m_statistics_num_frames;
    StateStack m_state_stack;
    TextureHolder m_textures;
    FontHolder m_font_holder;
    sf::Music m_music;
};

#endif