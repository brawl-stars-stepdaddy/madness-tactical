#include "GameOverEventData.hpp"

EventType GameOverEventData::get_event_type() const {
    return EventType::GAME_OVER;
}