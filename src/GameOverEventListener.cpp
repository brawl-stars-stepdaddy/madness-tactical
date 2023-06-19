#include "GameOverEventListener.hpp"
#include <cassert>

void GameOverEventListener::process(const EventData &event) {
    assert(event.get_event_type() == EventType::GAME_OVER);
    auto game_over_event = static_cast<const GameOverEventData &>(event);
}
