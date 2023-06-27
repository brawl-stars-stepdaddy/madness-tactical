#include "game_objects/entities/Box.hpp"
#include "logic/World.hpp"
#include "logic/events/event_data/DestructionEventData.hpp"

Box::Box(World &world) : Entity(world) {
}

void Box::draw_current(sf::RenderTarget &target, sf::RenderStates states)
    const {
    target.draw(m_sprite, states);
}

void Box::update_current([[maybe_unused]] sf::Time delta_time) {
    Entity::update_current(delta_time);
    if (get_body().get_b2Body()->IsAwake()) {
        m_world->set_world_at_rest(false);
    }
}

RectBody &Box::get_body() {
    return m_body;
}

EntityType Box::get_type() {
    return EntityType::BOX;
}

void Box::on_collision(std::shared_ptr<Entity> other_object) {
    if (other_object->get_type() == EntityType::PLANET_CORE) {
        m_body.get_b2Body()->SetEnabled(false);
        m_world->get_event_manager()->queue_event(
            std::make_unique<DestructionEventData>(this)
        );
    }
}

void Box::on_explosion(const Explosion &) {
    m_body.get_b2Body()->SetEnabled(false);
    m_world->get_event_manager()->queue_event(
        std::make_unique<DestructionEventData>(this)
    );
}
