#ifndef MOVE_TRANSITION_LOGIC_STATE_HPP_
#define MOVE_TRANSITION_LOGIC_STATE_HPP_

#include "logic/controllers/Controller.hpp"
#include "logic/states/GameState.hpp"

struct MoveTransitionLogicState : State {
public:
    MoveTransitionLogicState(StateStack &stack,
                             Context context,
                             GameState &game_state
                             );

    void draw() override;
    bool update(sf::Time delta_time) override;
    bool handle_input(const sf::Event &event) override;
    bool handle_realtime_input() override;

private:
    sf::Time m_timer = sf::seconds(8);
    GameState *m_game_state;
    float m_box_fall_distance = 100.0f;
    float m_box_fall_impulse = -0.1f;
};

#endif  // MOVE_TRANSITION_LOGIC_STATE_HPP_
