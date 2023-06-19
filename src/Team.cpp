#include "Team.hpp"
#include "Unit.hpp"

Team::Team(sf::Color color) : m_team_color(color) {
}

void Team::add_unit(Unit *unit) {
    auto unit_position =
        std::find(m_team_units.begin(), m_team_units.end(), unit);
    if (unit_position == m_team_units.end()) {
        unit->set_team(this);
        m_team_units.push_back(unit);
        m_team_size++;
    }
}

void Team::remove_unit(Unit *unit) {
    auto unit_position =
        std::find(m_team_units.begin(), m_team_units.end(), unit);
    if (unit_position != m_team_units.end()) {
        m_team_units.erase(unit_position);
        m_team_size--;
    }
}

void Team::activate_team() {
    update_health();
    m_active_unit = (m_active_unit + 1) % m_team_size;
    m_team_units[m_active_unit]->set_activeness(true);
}

void Team::deactivate_team() {
    update_health();
    m_team_units[m_active_unit]->set_activeness(false);
}

Unit *Team::activate_next_unit() {
    deactivate_team();
    activate_team();
    return m_team_units[m_active_unit];
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

void Team::add_weapon(WeaponType type) {
    m_available_weapons[type]++;
}

void Team::remove_weapon(WeaponType type) {
    m_available_weapons[type]--;
}

int Team::get_available_number(WeaponType type) {
    return m_available_weapons[type];
}

sf::Color Team::get_team_color() {
    return m_team_color;
}
