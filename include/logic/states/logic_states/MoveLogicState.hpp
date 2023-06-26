#ifndef LOGIC_MOVE_STATE_HPP_
#define LOGIC_MOVE_STATE_HPP_

#include "logic/controllers/Controller.hpp"
#include "logic/states/GameState.hpp"

struct MoveLogicState : State {
public:
    MoveLogicState(StateStack &stack, Context context, GameState &game_state);

    void draw() override;
    bool update(sf::Time delta_time) override;
    bool handle_input(const sf::Event &event) override;
    bool handle_realtime_input() override;
    void set_controller(std::unique_ptr<Controller> controller);

private:
    sf::Time m_timer = sf::seconds(10);
    std::unique_ptr<Controller> m_controller = nullptr;
    GameState *m_game_state;
    sf::Text m_timer_text;
};

#endif // LOGIC_MOVE_STATE_HPP_
