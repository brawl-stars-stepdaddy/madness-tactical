#ifndef MOVE_TRANSITION_DATA_HPP_
#define MOVE_TRANSITION_DATA_HPP_

#include "EventData.hpp"
#include "SceneNode.hpp"

struct MoveTransitionEventData : EventData {
public:
    enum class TransitionType { OTHER_UNIT, OTHER_PLAYER };

    explicit MoveTransitionEventData(TransitionType);

    [[nodiscard]] EventType get_event_type() const override;

    [[nodiscard]] TransitionType get_transition_type() const;

private:
    TransitionType m_transition_type;
};

#endif  // MOVE_TRANSITION_DATA_HPP_
