#ifndef BLOODY_FATALITY_LOGIC_STATE_HPP_
#define BLOODY_FATALITY_LOGIC_STATE_HPP_

#include "GameState.hpp"
#include "Controller.hpp"

struct BloodyFatalityLogicState : State {
public:
    BloodyFatalityLogicState(StateStack &stack, Context context, GameState &game_state);
    virtual void draw() override;
    virtual bool update(sf::Time delta_time) override;
    virtual bool handle_input(const sf::Event &event) override;
    virtual bool handle_realtime_input() override;

private:
    sf::Time m_timer = sf::seconds(1);
    std::unique_ptr<Controller> m_controller = nullptr;
    GameState *m_game_state;
};

#endif // BLOODY_FATALITY_LOGIC_STATE_HPP_
