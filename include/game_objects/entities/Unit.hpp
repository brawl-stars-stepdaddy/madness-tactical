#ifndef UNIT_HPP_
#define UNIT_HPP_

#include "Entity.hpp"
#include "game_objects/bodies/UnitBody.hpp"

struct Weapon;
struct World;
struct Team;

struct Unit : Entity {
public:
    Unit(World &world, sf::Vector2f center, float radius);

    sf::Vector2f get_camera_position() const;

    UnitBody &get_body() override;
    EntityType get_type() override;

    void set_team(Team *);
    Team *get_team() const;

    void change_health(int);
    int get_health() const;

    void set_direction(float direction);
    float get_direction() const;

    void set_weapon(Weapon *weapon);
    Weapon *get_weapon() const;

    void on_collision(std::shared_ptr<Entity> other_object) override;
    void on_explosion(const Explosion &explosion) override;

    void set_moving_active(bool value);
    void set_dumping_active(bool value);
    void reset();

    void move(sf::Time delta_time, float direction);
    void stop_move(sf::Time delta_time);
    void jump_forward();
    void jump_backward();

    bool get_jumping_active() const;

    void set_activeness(bool value);
    void kill_unit();

    const sf::Sprite &get_sprite() const;

private:
    void draw_current(sf::RenderTarget &target, sf::RenderStates states) const override;
    void update_current(sf::Time delta_time) override;

    sf::Sprite m_sprite;
    UnitBody m_body;
    Weapon *m_weapon = nullptr;
    Team *m_team = nullptr;

    float m_direction = 1.0f;
    int m_health = 100;
    bool m_jumping_active = false;
    bool m_moving_active = false;
    bool m_dumping_active = false;
    bool m_is_active = false;
};

#endif // UNIT_HPP_