#include "TeamManager.hpp"
#include "Team.hpp"

Team *TeamManager::create_team() {
    m_teams.push_back(std::make_unique<Team>());
    m_team_number++;
    return m_teams[m_team_number - 1].get();
}

void TeamManager::move_transition() {
    remove_empty_teams();
    m_teams[m_active_team]->deactivate_team();
    m_active_team = (m_active_team + 1) % m_team_number;
    m_teams[m_active_team]->activate_team();
}

Team *TeamManager::get_active_team() const {
    return m_teams[m_active_team].get();
}

void TeamManager::remove_empty_teams() {
    m_teams.erase(std::remove_if(m_teams.begin(), m_teams.end(), [](const auto& team){
        return team->get_team_size() == 0;
    }), m_teams.end());
    m_team_number = static_cast<int>(m_teams.size());
}
