#include "ContactListener.hpp"
#include <memory>
#include "CollisionEventData.hpp"
#include "Entity.hpp"
#include "World.hpp"

void ContactListener::BeginContact(b2Contact *contact) {
    auto *first_object = reinterpret_cast<Entity *>(
            contact->GetFixtureA()->GetBody()->GetUserData().pointer
    );
    auto *second_object = reinterpret_cast<Entity *>(
            contact->GetFixtureB()->GetBody()->GetUserData().pointer
    );
    m_world->get_event_manager()->queue_event(
        std::make_unique<CollisionEventData>(first_object, second_object, CollisionEventData::CollisionType::BEGIN_CONTACT)
    );
}

void ContactListener::EndContact(b2Contact *contact) {
    auto *first_object = reinterpret_cast<Entity *>(
            contact->GetFixtureA()->GetBody()->GetUserData().pointer
    );
    auto *second_object = reinterpret_cast<Entity *>(
            contact->GetFixtureB()->GetBody()->GetUserData().pointer
    );
    m_world->get_event_manager()->queue_event(
            std::make_unique<CollisionEventData>(first_object, second_object, CollisionEventData::CollisionType::END_CONTACT)
    );
}

ContactListener::ContactListener(World &world) : m_world(&world) {

}
