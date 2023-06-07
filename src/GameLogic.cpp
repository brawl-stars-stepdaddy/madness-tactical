#include "GameLogic.hpp"
#include "World.hpp"

GameLogic::GameLogic() {

}

GameLogic::GameLogic(World *world) : m_world(world) {

}

Unit *GameLogic::get_current_unit() {
    //return m_team_manager.get_active_team()->get_active_unit();
    return m_world->get_player();
}

World *GameLogic::get_world() {
    return m_world;
}
