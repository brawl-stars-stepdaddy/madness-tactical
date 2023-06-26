#include "WeaponSelectLogicState.hpp"
#include "Weapon.hpp"
#include "Button.hpp"
#include "StateStack.hpp"
#include "MoveLogicState.hpp"
#include "Label.hpp"

WeaponSelectLogicState::WeaponSelectLogicState(StateStack &stack, State::Context context, GameState &game_state) : State(stack, context), m_game_state(&game_state) {
    for (int weapon_type = 0; weapon_type < WEAPON_TYPES_NUMBER; weapon_type++) {
        auto weapon_button = std::make_unique<GUI::Button>(*context.fonts);
        weapon_button->setPosition(context.window->getView().getSize() / 2.f + sf::Vector2f{0, (weapon_type - WEAPON_TYPES_NUMBER / 2.f) * 100});
        weapon_button->set_text(Weapon::weapon_name(static_cast<WeaponType>(weapon_type)));
        weapon_button->set_callback([this, weapon_type, &game_state]() {
            request_stack_pop();
            Unit *unit = m_game_state->get_team_manager()->get_active_team()->get_active_unit();
            unit->get_weapon()->detach();
            auto weapon = Weapon::make_weapon(static_cast<WeaponType>(weapon_type), game_state.get_world(), unit);
            unit->set_weapon(weapon.get());
            weapon->set_hidden(false);
            unit->attach_child(weapon);
            auto camera = game_state.get_world()->get_camera();
            if (weapon->get_controller_type() == LAUNCH) {
                camera->set_follow_strategy(std::make_unique<SmoothFollowStrategy>(camera, std::static_pointer_cast<Unit>(unit->get_pointer())));
                reinterpret_cast<MoveLogicState *>(game_state.get_logic_state_stack()->front())->set_controller(std::make_unique<LaunchWeaponController>(game_state));
            } else {
                camera->set_follow_strategy(std::make_unique<ControlledFollowStrategy>(camera));
                reinterpret_cast<MoveLogicState *>(game_state.get_logic_state_stack()->front())->set_controller(std::make_unique<DistantWeaponController>(game_state));
            }
        });
        m_weapon_table.pack(std::move(weapon_button));

        auto weapon_count_label = std::make_unique<GUI::Label>(std::to_string(game_state.get_team_manager()->get_active_team()->get_available_number_weapons(static_cast<WeaponType>(weapon_type))), *context.fonts);
        weapon_count_label->setPosition(context.window->getView().getSize() / 2.f + sf::Vector2f{100, (weapon_type - WEAPON_TYPES_NUMBER / 2.f) * 100});
        m_weapon_count.pack(std::move(weapon_count_label));
    }
}

void WeaponSelectLogicState::draw() {
    get_context().window->setView(get_context().window->getDefaultView());
    sf::RectangleShape background;
    background.setFillColor(sf::Color(0, 0, 0, 150));
    background.setSize(sf::Vector2f(get_context().window->getSize()));
    get_context().window->draw(background);
    get_context().window->draw(m_weapon_table);
    get_context().window->draw(m_weapon_count);
}

bool WeaponSelectLogicState::update(sf::Time delta_time) {
    return true;
}

bool WeaponSelectLogicState::handle_input(const sf::Event &event) {
    m_weapon_table.handle_input(event);
    return false;
}

bool WeaponSelectLogicState::handle_realtime_input() {
    return false;
}
