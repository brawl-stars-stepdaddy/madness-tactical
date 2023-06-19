#ifndef MADNESS_TACTICAL_GAMELOGIC_HPP
#define MADNESS_TACTICAL_GAMELOGIC_HPP

#include "TeamManager.hpp"

struct World;
struct Unit;

struct GameLogic {
public:
    GameLogic();
    explicit GameLogic(World *world);
    Unit *get_current_unit();
    World *get_world();

private:
    TeamManager m_team_manager;
    World *m_world;
};

#endif  // MADNESS_TACTICAL_GAMELOGIC_HPP
