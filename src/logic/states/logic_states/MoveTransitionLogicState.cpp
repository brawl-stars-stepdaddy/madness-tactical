#include <random>
#include "logic/states/logic_states/MoveTransitionLogicState.hpp"
#include "game_objects/entities/HealingBox.hpp"
#include "game_objects/entities/WeaponBox.hpp"

MoveTransitionLogicState::MoveTransitionLogicState(
    StateStack &stack,
    State::Context context,
    GameState &game_state
)
    : State(stack, context), m_game_state(&game_state) {
    auto camera = m_game_state->get_world()->get_camera();
    auto layer = m_game_state->get_world()->get_layer(World::Layer::ENTITIES);

    std::mt19937 rand_gen((std::random_device()()));
    int box_type = (std::uniform_int_distribution<int>(0, 1))(rand_gen);
    float angle =
        (std::uniform_real_distribution<float>(0, 2 * M_PI))(rand_gen);
    std::shared_ptr<Box> box;
    b2Vec2 position = {
        cos(angle) * m_box_fall_distance, sin(angle) * m_box_fall_distance};

    if (box_type) {
        box = std::make_shared<WeaponBox>(
            *m_game_state->get_world(),
            sf::FloatRect(position.x, position.y, 1.5, 1)
        );
    } else {
        box = std::make_shared<HealingBox>(
            *m_game_state->get_world(),
            sf::FloatRect(position.x, position.y, 1.5, 1)
        );
    }
    camera->set_follow_strategy(
        std::make_unique<SmoothFollowStrategy>(camera, box)
    );
    position *= m_box_fall_impulse;
    box->get_body().get_b2Body()->SetLinearVelocity(position);
    layer->attach_child(std::move(box));
}

void MoveTransitionLogicState::draw() {}

bool MoveTransitionLogicState::update(sf::Time delta_time) {
    m_timer -= delta_time;
    if (m_timer <= sf::Time::Zero) {
        request_stack_clear();
        if (m_game_state->get_team_manager()->get_number_available_teams() <=
            1) {
            request_stack_push(StatesID::GAME_OVER);
        } else {
            m_game_state->get_team_manager()->move_transition();
            request_stack_push(StatesID::MOVE);
        }
    }
    return false;
}

bool MoveTransitionLogicState::handle_input(const sf::Event &event) {
    return false;
}

bool MoveTransitionLogicState::handle_realtime_input() {
    return false;
}
