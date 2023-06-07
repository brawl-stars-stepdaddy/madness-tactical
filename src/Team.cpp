#include "Team.hpp"
#include "Unit.hpp"

void Team::add_unit(Unit *unit) {
    auto unit_position = std::find(m_team_units.begin(), m_team_units.end(), unit);
    if (unit_position == m_team_units.end()) {
        unit->set_team(this);
        m_team_units.push_back(unit);
        m_team_size++;
    }
}

void Team::remove_unit(Unit *unit) {
    auto unit_position = std::find(m_team_units.begin(), m_team_units.end(), unit);
    if (unit_position != m_team_units.end()) {
        m_team_units.erase(unit_position);
        m_team_size--;
    }
}

void Team::move_transition() {
    update_health();
    m_active_unit = (m_active_unit + 1) % m_team_size;
}

Unit *Team::get_active_unit() const {
    return m_team_units[m_active_unit];
}

int Team::get_team_size() const {
    return m_team_size;
}

void Team::update_health() {
    m_summary_health = 0;
    for (auto unit : m_team_units) {
        m_summary_health += unit->get_health();
    }
}
