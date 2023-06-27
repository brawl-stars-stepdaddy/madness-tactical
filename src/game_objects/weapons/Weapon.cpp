#include "game_objects/weapons/Weapon.hpp"
#include "logic/World.hpp"
#include "logic/states/GameState.hpp"
#include "game_objects/weapons/Bazooka.hpp"
#include "game_objects/weapons/Laser.hpp"
#include "game_objects/weapons/Grenade.hpp"
#include "game_objects/weapons/LandMine.hpp"
#include "game_objects/weapons/Kettlebell.hpp"
#include "game_objects/weapons/Armageddon.hpp"

Weapon::Weapon(World &world) : SceneNode(world) {}

void Weapon::set_hidden(bool new_value) {
    m_is_hidden = new_value;
}

void Weapon::launch() {
    set_hidden(true);
    auto game_state = dynamic_cast<GameState *>(m_world->get_game_state());
    game_state->get_logic_state_stack()->clear_states();
    game_state->get_logic_state_stack()->push_state(StatesID::POST_MOVE);
}

std::string Weapon::weapon_name(WeaponType weapon_type) {
    static std::vector<std::string> weapon_names { "bazooka", "laser", "grenade", "land mine", "kettleball", "armageddon", };
    return weapon_names[weapon_type];
}

std::shared_ptr<Weapon> Weapon::make_weapon(WeaponType weapon_type, World *world, Unit *unit) {
    if (weapon_type == BAZOOKA) {
        return std::make_shared<Bazooka>(*world, unit);
    } else if (weapon_type == LASER) {
        return std::make_shared<Laser>(*world, unit);
    } else if (weapon_type == GRENADE) {
        return std::make_shared<Grenade>(*world, unit);
    } else if (weapon_type == LAND_MINE) {
        return std::make_shared<LandMine>(*world, unit);
    } else if (weapon_type == KETTLEBELL) {
        return std::make_shared<Kettlebell>(*world, unit);
    } else if (weapon_type == ARMAGEDDON) {
        return std::make_shared<Armageddon>(*world, unit);
    }
    return nullptr;
}

