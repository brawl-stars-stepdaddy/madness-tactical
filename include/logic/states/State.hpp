#ifndef STATE_HPP_
#define STATE_HPP_

#include <SFML/Graphics/RenderWindow.hpp>
#include <memory>
#include "StateIdentifiers.hpp"
#include "utils/ResourceIdentifiers.hpp"

struct StateStack;

struct State {
public:
    typedef std::unique_ptr<State> Ptr;

    struct Context {
    public:
        Context(sf::RenderWindow &window,
                TextureHolder &textures,
                FontHolder &fonts
                );

        sf::RenderWindow *window;
        TextureHolder *textures;
        FontHolder *fonts;
    };

    State(StateStack &stack, Context context);

    virtual ~State() = default;

    virtual void draw() = 0;
    virtual bool update(sf::Time delta_time) = 0;
    virtual bool handle_input(const sf::Event &event) = 0;
    virtual bool handle_realtime_input() = 0;

protected:
    void request_stack_push(StatesID state_id);
    void request_stack_pop();
    void request_stack_clear();

    [[nodiscard]] Context get_context() const;

private:
    StateStack *m_stack;
    Context m_context;
};

#endif // STATE_HPP_
