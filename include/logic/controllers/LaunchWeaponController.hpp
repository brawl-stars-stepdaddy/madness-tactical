#ifndef MADNESS_TACTICAL_LAUNCHWEAPONCONTROLLER_HPP
#define MADNESS_TACTICAL_LAUNCHWEAPONCONTROLLER_HPP

#include "Controller.hpp"

struct GameState;

struct LaunchWeaponController : Controller {
public:
    explicit LaunchWeaponController(GameState &game_state);

private:
    GameState *m_game_state;
};

#endif
