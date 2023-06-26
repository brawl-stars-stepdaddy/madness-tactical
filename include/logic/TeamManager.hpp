#ifndef TEAM_MANAGER_HPP_
#define TEAM_MANAGER_HPP_

#include <memory>
#include <vector>
#include "Team.hpp"

struct Unit;

struct TeamManager {
public:
    void move_transition(bool init_state = false);

    Team *create_team(sf::Color);
    [[nodiscard]] Team *get_active_team(bool init_state = false) const;

    [[nodiscard]] int get_number_available_teams() const;
    [[nodiscard]] int get_number_available_units() const;

private:
    std::vector<std::unique_ptr<Team>> m_teams;
    int m_active_team = 0;
    int m_team_number = 0;
};

#endif  // TEAM_MANAGER_HPP_
