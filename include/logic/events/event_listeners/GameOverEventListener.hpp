#ifndef GAME_OVER_LISTENER_HPP_
#define GAME_OVER_LISTENER_HPP_

#include "EventListener.hpp"
#include "logic/events/event_data/GameOverEventData.hpp"

struct GameOverEventListener : EventListener {
public:
    void process(const EventData &event) override;
};

#endif  // GAME_OVER_LISTENER_HPP_
