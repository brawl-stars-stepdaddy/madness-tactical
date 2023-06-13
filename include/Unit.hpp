#ifndef UNIT_HPP_
#define UNIT_HPP_

#include "JumpSensor.hpp"
#include "Entity.hpp"
#include "UnitBody.hpp"
#include "JumpSensor.hpp"

struct Weapon;
struct World;
struct Team;

struct Unit : Entity {
public:
    enum class Type {
        ENGINEER,
        WORM,
    };

    Unit(World &world, Type type, sf::Vector2f, float, int);

    UnitBody &get_body() override;
    EntityType get_type() override;

    void set_team(Team *);
    Team *get_team() const;

    void change_health(int);
    int get_health() const;

    void set_direction(float direction);
    float get_direction() const;

    void set_weapon(Weapon *);
    Weapon *get_weapon() const;

    void on_collision(Entity *) override;
    void on_explosion(const Explosion &) override;

    void set_moving_active(bool);
    void set_dumping_active(bool);
    void reset();

    void move(sf::Time, float);
    void stop_move(sf::Time);
    void jump_forward();
    void jump_backward();

    void set_activeness(bool);
    void kill_unit();

private:
    void draw_current(sf::RenderTarget &target, sf::RenderStates)
        const override;

    void update_current(sf::Time delta_time) override;

    sf::Sprite m_sprite;
    Type m_type;
    UnitBody m_body;
    Weapon *m_weapon;
    Team *m_team = nullptr;
    float m_direction = 1.0f;
    int m_health = 100;
    int m_player_id;
    bool m_jumping_active = false;
    bool m_moving_active = false;
    bool m_dumping_active = false;
    bool m_is_active = false;
};


#endif