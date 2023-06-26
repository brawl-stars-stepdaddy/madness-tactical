#include "Weapon.hpp"
#include "World.hpp"
#include "GameState.hpp"

Weapon::Weapon(World &world) : SceneNode(world) {
}

void Weapon::set_hidden(bool new_value) {
    m_is_hidden = new_value;
}

void Weapon::launch() {
    auto game_state = static_cast<GameState *>(m_world->get_game_state());
    game_state->get_logic_state_stack()->clear_states();
    game_state->get_logic_state_stack()->push_state(StatesID::PostMove);
}
