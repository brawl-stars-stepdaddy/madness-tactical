#ifndef MADNESS_TACTICAL_GAMELOGIC_HPP
#define MADNESS_TACTICAL_GAMELOGIC_HPP

struct World;
struct Unit;

struct GameLogic {
public:
    GameLogic();
    explicit GameLogic(World *world);
    Unit *get_current_unit();
    World *get_world() {
        return m_world;
    }

private:
    World *m_world;
};

#endif //MADNESS_TACTICAL_GAMELOGIC_HPP
