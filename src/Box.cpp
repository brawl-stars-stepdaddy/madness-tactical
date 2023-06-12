#include "Box.hpp"
#include "DestructionEventData.hpp"
#include "World.hpp"

Box::Box(World &world) : Entity(world) {

}

void Box::draw_current(sf::RenderTarget &target, sf::RenderStates states)
    const {
    target.draw(m_sprite, states);
}

void Box::update_current([[maybe_unused]] sf::Time delta_time) {
    Entity::update_current(delta_time);
}

RectBody &Box::get_body() {
    return m_body;
}

EntityType Box::get_type() {
    return EntityType::BOX;
}

void Box::on_collision(Entity *) {
}

void Box::on_explosion(const Explosion &) {
    m_body.get_b2Body()->SetEnabled(false);
    m_world->get_event_manager()->queue_event(
            std::make_unique<DestructionEventData>(this)
    );
}
