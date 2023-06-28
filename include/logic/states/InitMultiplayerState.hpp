#ifndef INITMULTIPLAYERSTATE_HPP
#define INITMULTIPLAYERSTATE_HPP

#include <SFML/Graphics.hpp>
#include "logic/states/State.hpp"
#include "logic/GameClient.hpp"

struct InitMultiplayerState : State {
public:
    InitMultiplayerState(StateStack &stack, Context context);

    void draw() override;
    bool update(sf::Time delta_time) override;
    bool handle_input(const sf::Event &event) override;
    bool handle_realtime_input() override;

private:
    std::unique_ptr<GameClient> m_game_client;
    sf::Text m_text;
    sf::Sprite m_background;
};

#endif
