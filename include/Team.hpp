#ifndef TEAM_HPP_
#define TEAM_HPP_

#include <vector>
#include <algorithm>

struct Unit;

struct Team {
    void add_unit(Unit *);
    void remove_unit(Unit *);

    void move_transition();

    Unit *get_active_unit() const;
    int get_team_size() const;

private:
    std::vector<Unit *> m_team_units;
    int m_active_unit = 0;
    int m_team_size = 0;
    int m_summary_health = 0;

    void update_health();
};

#endif // TEAM_HPP_
