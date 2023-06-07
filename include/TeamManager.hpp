#ifndef TEAM_MANAGER_HPP_
#define TEAM_MANAGER_HPP_

#include <vector>
#include <memory>
#include <algorithm>
#include "Team.hpp"

struct Unit;

struct TeamManager {
    Team *create_team();

    void move_transition();

    [[nodiscard]] Team *get_active_team() const;

private:
    std::vector<std::unique_ptr<Team>> m_teams;
    int m_active_team = 0;
    int m_team_number = 0;

    void remove_empty_teams();
};

#endif // TEAM_MANAGER_HPP_
