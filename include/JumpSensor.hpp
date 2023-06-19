#ifndef JUMP_SENSOR_HPP_
#define JUMP_SENSOR_HPP_

#include "CollisionEventData.hpp"
#include "Entity.hpp"
#include "JumpSensorBody.hpp"

struct Unit;
struct World;

struct JumpSensor : Entity {
public:
    JumpSensor(World &world, Unit *, sf::Vector2f center, float radius);

    Body &get_body() override;
    void on_collision(Entity *);
    void end_collision(Entity *);
    EntityType get_type() override;

    void on_explosion(const Explosion &) override{};

private:
    Unit *m_parent;
    JumpSensorBody m_body;
};

#endif  // JUMP_SENSOR_HPP_
