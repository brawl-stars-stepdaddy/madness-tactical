#include <State.hpp>
#include <StateStack.hpp>

State::Context::Context(
    sf::RenderWindow &window,
    TextureHolder &textures,
    FontHolder &fonts
)
    : window(&window), textures(&textures), fonts(&fonts) {
}

State::State(StateStack &stack, State::Context context)
    : m_stack(&stack), m_context(context) {
}

void State::request_stack_push(StatesID state_id) {
    m_stack->push_state(state_id);
}

void State::request_stack_pop() {
    m_stack->pop_state();
}

void State::request_stack_clear() {
    m_stack->clear_states();
}

State::Context State::get_context() const {
    return m_context;
}
