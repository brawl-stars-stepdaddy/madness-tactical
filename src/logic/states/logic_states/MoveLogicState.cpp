#include "game_objects/entities/Unit.hpp"
#include "game_objects/weapons/Weapon.hpp"
#include "logic/states/logic_states/MoveLogicState.hpp"
#include "logic/controllers/LaunchWeaponController.hpp"
#include "logic/controllers/DistantWeaponController.hpp"
#include "utils/GuiUtil.hpp"
#include "utils/ResourceHolder.hpp"

MoveLogicState::MoveLogicState(
    StateStack &stack,
    State::Context context,
    GameState &game_state
)
    : State(stack, context), m_game_state(&game_state) {
    m_game_state->get_world()->set_active_unit(
        m_game_state->get_team_manager()->get_active_team()->get_active_unit()
    );
    auto unit = std::static_pointer_cast<Unit>(m_game_state->get_team_manager()
                                                   ->get_active_team()
                                                   ->get_active_unit()
                                                   ->get_pointer());
    auto camera = m_game_state->get_world()->get_camera();
    if (unit->get_weapon()->get_controller_type() == LAUNCH) {
        m_controller = std::make_unique<LaunchWeaponController>(game_state);
        camera->set_follow_strategy(
            std::make_unique<SmoothFollowStrategy>(camera, unit)
        );
    } else {
        m_controller = std::make_unique<DistantWeaponController>(game_state);
        camera->set_follow_strategy(
            std::make_unique<ControlledFollowStrategy>(camera)
        );
    }
    m_timer_text.setFont(get_context().fonts->get(FontsID::SANSATION));
    m_timer_text.setOutlineThickness(3.f);
    m_timer_text.setOutlineColor(sf::Color::Black);
    m_timer_text.setFillColor(sf::Color::White);
    m_timer_text.setCharacterSize(80);
    m_timer_text.setPosition(
        get_context().window->getView().getSize().x / 2.f,
        static_cast<float>(m_timer_text.getCharacterSize())
    );
}

void MoveLogicState::draw() {
    get_context().window->setView(get_context().window->getDefaultView());
    get_context().window->draw(m_timer_text);
}

bool MoveLogicState::update(sf::Time delta_time) {
    m_timer -= delta_time;
    m_timer_text.setString(std::to_string(static_cast<int>(m_timer.asSeconds())));
    GuiUtil::center(m_timer_text);
    if (m_timer <= sf::Time::Zero) {
        request_stack_clear();
        request_stack_push(StatesID::BLOODY_FATALITY);
    }
    return false;
}

bool MoveLogicState::handle_input(const sf::Event &event) {
    if (event.type == sf::Event::KeyReleased && event.key.code == sf::Keyboard::E) {
        request_stack_push(StatesID::WEAPON_SELECT);
    } else {
        m_controller->handle_input(event);
    }
    return false;
}

bool MoveLogicState::handle_realtime_input() {
    m_controller->handle_realtime_input();
    return false;
}

void MoveLogicState::set_controller(std::unique_ptr<Controller> controller) {
    m_controller = std::move(controller);
}
