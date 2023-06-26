#include "logic/states/StateStack.hpp"
#include <cassert>

StateStack::StateStack(State::Context context) : m_context(context) {
}

void StateStack::update(sf::Time delta_time) {
    for (auto it = m_stack.rbegin(); it != m_stack.rend(); it++) {
        if (!(*it)->update(delta_time)) {
            break;
        }
    }
    apply_pending_changes();
}

void StateStack::draw() {
    for (auto it = m_stack.begin(); it != m_stack.end(); it++) {
        (*it)->draw();
    }
}

void StateStack::handle_input(const sf::Event &event) {
    for (auto it = m_stack.rbegin(); it != m_stack.rend(); it++) {
        if (!(*it)->handle_input(event)) {
            break;
        }
    }
    apply_pending_changes();
}

void StateStack::handle_realtime_input() {
    for (auto it = m_stack.rbegin(); it != m_stack.rend(); it++) {
        if (!(*it)->handle_realtime_input()) {
            break;
        }
    }
    apply_pending_changes();
}

State::Ptr StateStack::create_state(StatesID state_id) {
    auto found = m_factories.find(state_id);
    assert(found != m_factories.end());
    return found->second();
}

void StateStack::push_state(StatesID state_id) {
    m_pending_queue.push({Push, state_id});
}

void StateStack::pop_state() {
    m_pending_queue.push({Pop});
}

void StateStack::clear_states() {
    m_pending_queue.push({Clear});
}

bool StateStack::is_empty() {
    return m_stack.empty();
}

void StateStack::apply_pending_changes() {
    while (!m_pending_queue.empty()) {
        PendingChange change = m_pending_queue.front();
        m_pending_queue.pop();
        switch (change.action) {
            case Push:
                m_stack.push_back(create_state(change.state_id));
                break;
            case Pop:
                m_stack.pop_back();
                break;
            case Clear:
                m_stack.clear();
                break;
        }
    }
}
