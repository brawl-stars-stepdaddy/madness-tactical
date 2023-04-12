#ifndef DESTRUCTION_EVENT_DATA_HPP_
#define DESTRUCTION_EVENT_DATA_HPP_

#include "EventData.hpp"
#include "SceneNode.hpp"

struct DestructionEventData : EventData {
public:
    explicit DestructionEventData(SceneNode *);

    [[nodiscard]] EventType get_event_type() const override;

    [[nodiscard]] SceneNode *get_object() const;

private:
    SceneNode *m_object;
};

#endif  // DESTRUCTION_EVENT_DATA_HPP_
