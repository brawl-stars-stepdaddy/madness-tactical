#ifndef MADNESS_TACTICAL_WEAPONSELECTLOGICSTATE_HPP
#define MADNESS_TACTICAL_WEAPONSELECTLOGICSTATE_HPP

#include "State.hpp"
#include "GameState.hpp"
#include "Container.hpp"

struct WeaponSelectLogicState : State {
public:
    WeaponSelectLogicState(StateStack &stack, Context context, GameState &game_state);
    virtual void draw() override;
    virtual bool update(sf::Time delta_time) override;
    virtual bool handle_input(const sf::Event &event) override;
    virtual bool handle_realtime_input() override;

private:
    GameState *m_game_state;
    GUI::Container m_weapon_table;
    GUI::Container m_weapon_count;
};

#endif
