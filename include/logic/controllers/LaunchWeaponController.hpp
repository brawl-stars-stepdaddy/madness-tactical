#ifndef LAUNCH_WEAPON_CONTROLLER_HPP_
#define LAUNCH_WEAPON_CONTROLLER_HPP_

#include "Controller.hpp"

struct GameState;

struct LaunchWeaponController : Controller {
public:
    explicit LaunchWeaponController(GameState &game_state);

private:
    GameState *m_game_state;
};

#endif // LAUNCH_WEAPON_CONTROLLER_HPP_
