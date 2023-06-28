#ifndef MULTIPLAYER_GAME_STATE_HPP_
#define MULTIPLAYER_GAME_STATE_HPP_

#include "logic/states/GameState.hpp"
#include "StateStack.hpp"

struct MultiplayerGameState : GameState {
public:
    MultiplayerGameState(StateStack &stack, Context context);
};

#endif // MULTIPLAYER_GAME_STATE_HPP_
