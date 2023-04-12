#include "Box.hpp"
#include "EventManager.hpp"
#include "DestructionEventData.hpp"

void Box::draw_current(sf::RenderTarget &target, sf::RenderStates states)
    const {
    target.draw(m_sprite, states);
}

void Box::update_current(sf::Time delta_time) {
    setPosition(
        {m_body.get_position().x * World::SCALE,
         m_body.get_position().y * World::SCALE}
    );
    setRotation(m_body.get_rotation() * 60);
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
    EventManager::get()->queue_event(
            std::make_unique<DestructionEventData>(this)
    );
}
