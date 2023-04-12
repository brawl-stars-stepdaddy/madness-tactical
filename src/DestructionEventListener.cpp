#include "DestructionEventListener.hpp"

void DestructionEventListener::process(const EventData &event) {
    assert(event.get_event_type() == EventType::DESTRUCTION);
    auto destruction_event = static_cast<const DestructionEventData &>(event);
    if (deleted_objects.find(destruction_event.get_object()) == deleted_objects.end()) {
        destruction_event.get_object()->detach();
        deleted_objects.insert(destruction_event.get_object());
    }
}

void DestructionEventListener::reset() {
    deleted_objects.clear();
}


