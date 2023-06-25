#ifndef TEAM_MANAGER_HPP_
#define TEAM_MANAGER_HPP_

#include <algorithm>
#include <memory>
#include <vector>
#include "Team.hpp"

struct Unit;

struct TeamManager {
    Team *create_team(sf::Color);

    void move_transition();

    [[nodiscard]] Team *get_active_team() const;
    [[nodiscard]] int get_number_available_teams() const;

private:
    std::vector<std::unique_ptr<Team>> m_teams;
    int m_active_team = 0;
    int m_team_number = 0;
};

#endif  // TEAM_MANAGER_HPP_
