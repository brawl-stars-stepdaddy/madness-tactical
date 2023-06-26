#include "utils/ContactListener.hpp"
#include "game_objects/entities/Entity.hpp"
#include "logic/World.hpp"
#include "logic/events/event_data/CollisionEventData.hpp"

void ContactListener::BeginContact(b2Contact *contact) {
    auto first_object = std::static_pointer_cast<Entity>(
        reinterpret_cast<Entity *>(
            contact->GetFixtureA()->GetBody()->GetUserData().pointer
        )
            ->get_pointer()
    );
    auto second_object = std::static_pointer_cast<Entity>(
        reinterpret_cast<Entity *>(
            contact->GetFixtureB()->GetBody()->GetUserData().pointer
        )
            ->get_pointer()
    );
    m_world->get_event_manager()->queue_event(
        std::make_unique<CollisionEventData>(
            first_object, second_object,
            CollisionEventData::CollisionType::BEGIN_CONTACT
        )
    );
}

void ContactListener::EndContact(b2Contact *contact) {
    auto first_object = std::static_pointer_cast<Entity>(
        reinterpret_cast<Entity *>(
            contact->GetFixtureA()->GetBody()->GetUserData().pointer
        )
            ->get_pointer()
    );
    auto second_object = std::static_pointer_cast<Entity>(
        reinterpret_cast<Entity *>(
            contact->GetFixtureB()->GetBody()->GetUserData().pointer
        )
            ->get_pointer()
    );
    m_world->get_event_manager()->queue_event(
        std::make_unique<CollisionEventData>(
            first_object, second_object,
            CollisionEventData::CollisionType::END_CONTACT
        )
    );
}

ContactListener::ContactListener(World &world) : m_world(&world) {}
