#ifndef TEAM_HPP_
#define TEAM_HPP_

#include <algorithm>
#include <map>
#include <vector>
#include "game_objects/weapons/Weapon.hpp"

struct Unit;

struct Team {
    explicit Team(sf::Color);

    void add_unit(Unit *);
    void remove_unit(Unit *);

    void add_weapon(WeaponType);
    void remove_weapon(WeaponType);

    int get_available_number_weapons(WeaponType);
    sf::Color get_team_color();

    void activate_team();
    void deactivate_team();

    Unit *activate_next_unit();

    void change_health(int value);

    [[nodiscard]] Unit *get_active_unit() const;
    [[nodiscard]] int get_team_size() const;

private:
    sf::Color m_team_color;
    std::vector<Unit *> m_team_units;
    std::map<WeaponType, int> m_available_weapons;
    int m_active_unit = 0;
    int m_team_size = 0;
    int m_summary_health = 0;
};

#endif  // TEAM_HPP_
