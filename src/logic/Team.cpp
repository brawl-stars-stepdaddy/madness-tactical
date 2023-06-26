#include "logic/Team.hpp"
#include "game_objects/entities/Unit.hpp"

Team::Team(sf::Color color) : m_team_color(color) {
    m_available_weapons[BAZOOKA] = 10;
    m_available_weapons[GRENADE] = 10;
}

void Team::add_unit(Unit *unit) {
    auto unit_position =
        std::find(m_team_units.begin(), m_team_units.end(), unit);
    if (unit_position == m_team_units.end()) {
        unit->set_team(this);
        m_team_units.push_back(unit);
        m_team_size++;
        change_health(unit->get_health());
    }
}

void Team::remove_unit(Unit *unit) {
    auto unit_position =
        std::find(m_team_units.begin(), m_team_units.end(), unit);
    if (unit_position != m_team_units.end()) {
        if (unit_position - m_team_units.begin() <= m_active_unit) {
            m_active_unit--;
        }
        m_team_units.erase(unit_position);
        m_team_size--;
        change_health(-unit->get_health());
    }
}

void Team::activate_team() {
    if (m_team_size) {
        m_active_unit = (m_active_unit + 1) % m_team_size;
        m_team_units[m_active_unit]->set_activeness(true);
    }
}

void Team::deactivate_team() {
    if (m_active_unit < m_team_size) {
        m_team_units[m_active_unit]->set_activeness(false);
    }
}

Unit *Team::activate_next_unit() {
    if (m_team_size) {
        deactivate_team();
        activate_team();
        return m_team_units[m_active_unit];
    } else {
        return nullptr;
    }
}

Unit *Team::get_active_unit() const {
    if (m_team_size) {
        return m_team_units[m_active_unit];
    } else {
        return nullptr;
    }
}

int Team::get_team_size() const {
    return m_team_size;
}

void Team::add_weapon(WeaponType type) {
    m_available_weapons[type]++;
}

void Team::remove_weapon(WeaponType type) {
    m_available_weapons[type]--;
}

int Team::get_available_number_weapons(WeaponType type) {
    return m_available_weapons[type];
}

sf::Color Team::get_team_color() {
    return m_team_color;
}

void Team::change_health(int value) {
    m_summary_health += value;
}
