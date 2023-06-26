#include "logic/TeamManager.hpp"
#include "logic/Team.hpp"

Team *TeamManager::create_team(sf::Color color) {
    m_teams.push_back(std::make_unique<Team>(color));
    m_team_number++;
    return m_teams[m_team_number - 1].get();
}

void TeamManager::move_transition(bool init_state) {
    m_teams[m_active_team]->deactivate_team();
    if (!init_state && get_number_available_teams()) {
        do {
            m_active_team = (m_active_team + 1) % m_team_number;
        } while (m_teams[m_active_team]->get_team_size() == 0);
        m_teams[m_active_team]->activate_team();
    } else if (init_state) {
        m_active_team = (m_active_team + 1) % m_team_number;
        m_teams[m_active_team]->activate_team();
    }
}

Team *TeamManager::get_active_team(bool init_state) const {
    if (init_state || get_number_available_teams()) {
        return m_teams[m_active_team].get();
    } else {
        return nullptr;
    }
}

int TeamManager::get_number_available_teams() const {
    return static_cast<int>(std::count_if(
        m_teams.begin(), m_teams.end(),
        [](const auto &team) { return team->get_team_size() > 0; }
    ));
}

int TeamManager::get_number_available_units() const {
    int number = 0;
    for (const auto &team : m_teams) {
        number += team->get_team_size();
    }
    return number;
}
