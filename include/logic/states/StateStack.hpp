#ifndef STATE_STACK_HPP_
#define STATE_STACK_HPP_

#include <SFML/Graphics.hpp>
#include <functional>
#include <queue>
#include "State.hpp"
#include "StateIdentifiers.hpp"

struct StateStack {
public:
    enum Action {
        Push,
        Pop,
        Clear,
    };

    explicit StateStack(State::Context context);

    template <typename T>
    void register_state(StatesID state_id);
    template <typename T, typename U>
    void register_state(StatesID state_id, U &t);

    void update(sf::Time delta_time);
    void draw();

    void handle_input(const sf::Event &event);
    void handle_realtime_input();

    void push_state(StatesID state_id);
    void pop_state();
    void clear_states();
    State *top();
    State *front();

    bool is_empty();

private:
    State::Ptr create_state(StatesID state_id);
    void apply_pending_changes();

    struct PendingChange {
        Action action;
        StatesID state_id;
    };

    std::vector<State::Ptr> m_stack;
    std::queue<PendingChange> m_pending_queue;
    State::Context m_context;
    std::map<StatesID, std::function<State::Ptr()>> m_factories;
};

template <typename T>
void StateStack::register_state(StatesID state_id) {
    m_factories[state_id] = [this]() {
        return State::Ptr(new T(*this, m_context));
    };
}

template <typename T, typename U>
void StateStack::register_state(StatesID state_id, U &arg) {
    m_factories[state_id] = [this, &arg]() {
        return State::Ptr(new T(*this, m_context, arg));
    };
}

#endif // STATE_STACK_HPP_
