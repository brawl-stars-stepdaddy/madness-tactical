#include <cassert>
#include "logic/events/event_listeners/GameOverEventListener.hpp"

void GameOverEventListener::process(const EventData &event) {
    assert(event.get_event_type() == EventType::GAME_OVER);
    auto game_over_event = dynamic_cast<const GameOverEventData &>(event);
}
