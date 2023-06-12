#include "World.hpp"
#include <random>
#include <chrono>
#include <vector>
#include "Bazooka.hpp"
#include "CollisionEventListener.hpp"
#include "DestructionEventListener.hpp"
#include "GameOverEventListener.hpp"
#include "EventManager.hpp"
#include "EventType.hpp"
#include "ExplosionEventData.hpp"
#include "ExplosionEventListener.hpp"
#include "MoveTransitionEventListener.hpp"
#include "ActionEventListener.hpp"
#include "ActionEventData.hpp"
#include "SpriteNode.hpp"
#include "WeaponBox.hpp"
#include "Unit.hpp"

std::vector<std::pair<float, float>> generate_naive_map() {
    std::mt19937 rng((uint32_t) std::chrono::steady_clock::now().time_since_epoch().count());
    std::normal_distribution <float> gen_real (0, 0.4);

    std::vector<std::pair<float, float>> points;
    float prev_y = 8.0f;
    for (int i = 0; i <= 3000; i++) {
        float x = static_cast<float>(i) / 10;
        prev_y += gen_real(rng);
        points.emplace_back(x, prev_y);
    }
    prev_y = 8.0f;
    for (int i = 0; i <= 3000; i++) {
        float cur_y = points[i].second;
        prev_y = prev_y + 0.02 * (cur_y - prev_y);
        points[i].second = prev_y;
    }
    points.emplace_back(300, 100);
    points.emplace_back(0, 100);
    for (int i = 0; i < points.size(); i++) {
        points[i].first -= 150;
    }
    return points;
}

World::World(State::Context &context, EventManager &event_manager)
    : m_context(context),
      m_event_manager(&event_manager),
      m_world_view(context.window->getDefaultView()),
      m_world_bounds(-150, -30, 300, 100),
      m_spawn_position(5.f, 5.f),
      m_active_unit(nullptr),
      m_physics_world({0, 20}),
      m_map(nullptr),
      m_game_logic(this),
      m_camera(nullptr),
      m_scene_graph(*this) {
    load_textures();
    build_scene();
    m_event_manager->add_listener(
        std::make_unique<ExplosionEventListener>(), EventType::EXPLOSION
    );
    auto collision_listener = std::make_unique<CollisionEventListener>(*this);
    m_collision_listener = collision_listener.get();
    m_event_manager->add_listener(std::move(collision_listener), EventType::COLLISION);
    auto destruction_listener = std::make_unique<DestructionEventListener>();
    m_destruction_listener = destruction_listener.get();
    m_event_manager->add_listener(std::move(destruction_listener), EventType::DESTRUCTION);
    m_event_manager->add_listener(std::make_unique<MoveRightEventListener>(*this, m_game_logic), EventType::MOVE_RIGHT);
    m_event_manager->add_listener(std::make_unique<MoveLeftEventListener>(*this, m_game_logic), EventType::MOVE_LEFT);
    m_event_manager->add_listener(std::make_unique<ChangeAngleUpEventListener>(*this, m_game_logic), EventType::CHANGE_ANGLE_UP);
    m_event_manager->add_listener(std::make_unique<ChangeAngleDownEventListener>(*this, m_game_logic), EventType::CHANGE_ANGLE_DOWN);
    m_event_manager->add_listener(std::make_unique<JumpForwardEventListener>(*this, m_game_logic), EventType::JUMP_FORWARD);
    m_event_manager->add_listener(std::make_unique<JumpBackwardEventListener>(*this, m_game_logic), EventType::JUMP_BACKWARD);
    m_event_manager->add_listener(std::make_unique<BeginChargeWeaponEventListener>(*this, m_game_logic), EventType::BEGIN_CHARGE_WEAPON);
    m_event_manager->add_listener(std::make_unique<LaunchProjectileEventListener>(*this, m_game_logic),EventType::LAUNCH_PROJECTILE);
    m_event_manager->add_listener(std::make_unique<ZoomInEventListener>(&m_camera), EventType::ZOOM_IN);
    m_event_manager->add_listener(std::make_unique<ZoomOutEventListener>(&m_camera),EventType::ZOOM_OUT);
    m_event_manager->add_listener(std::make_unique<MoveTransitionEventListener>(this), EventType::MOVE_TRANSITION);
    m_event_manager->add_listener(std::make_unique<GameOverEventListener>(), EventType::GAME_OVER);
}

void World::load_textures() {
    m_context.textures->load(TexturesID::BACKGROUND, "res/sky.jpg");
    m_context.textures->load(TexturesID::ENGINEER, "res/Engineer.jpg");
    m_context.textures->load(TexturesID::HALO, "res/HaloRender.jpg");
    m_context.textures->load(TexturesID::MAP_TEXTURE, "res/dirt.jpg");
    m_context.textures->load(TexturesID::WORM, "res/Worm.png");
    m_context.textures->load(TexturesID::CANON_BALL, "res/canon_ball.png");
    m_context.textures->load(TexturesID::WEAPON_BOX, "res/weapon_box.png");
    m_context.textures->load(TexturesID::BAZOOKA, "res/bazooka.png");
    m_context.textures->get(TexturesID::MAP_TEXTURE).setRepeated(true);
    m_context.textures->get(TexturesID::BACKGROUND).setRepeated(true);
}

void World::build_scene() {
    for (std::size_t i = 0; i < LAYER_COUNT; i++) {
        SceneNode::Ptr layer = std::make_unique<SceneNode>(*this);
        m_scene_layers[i] = layer.get();
        m_scene_graph.attach_child(std::move(layer));
    }
    std::unique_ptr<SpriteNode> background_sprite =
        std::make_unique<SpriteNode>(*this, m_context.textures->get(TexturesID::BACKGROUND), sf::IntRect(m_world_bounds.left * World::SCALE,
                                                                                         m_world_bounds.top * World::SCALE,
                                                                                         m_world_bounds.width * World::SCALE,
                                                                                         m_world_bounds.height * World::SCALE));
    background_sprite->setPosition(m_world_bounds.left * World::SCALE, m_world_bounds.top * World::SCALE);
    m_scene_layers[BACKGROUND]->attach_child(std::move(background_sprite));
    m_scene_layers[ENTITIES]->attach_child(std::make_unique<WeaponBox>(*this, sf::FloatRect(15, 1, 1.5, 1)));
    std::unique_ptr<Unit> worm1 =
        std::make_unique<Unit>(*this, Unit::Type::WORM, sf::Vector2f{1, 1}, 1, 0);
    m_active_unit = worm1.get();
    m_scene_layers[ENTITIES]->attach_child(std::move(worm1));
    std::unique_ptr<Unit> worm2 =
            std::make_unique<Unit>(*this, Unit::Type::ENGINEER, sf::Vector2f{10, 1}, 1, 1);
    auto second_unit = worm2.get();
    m_scene_layers[ENTITIES]->attach_child(std::move(worm2));
    std::unique_ptr<SpriteNode> halo =
        std::make_unique<SpriteNode>(*this, m_context.textures->get(TexturesID::HALO));

    m_last_active_units.resize(2);
    m_playable_units.resize(2);
    m_playable_units[0].push_back(m_active_unit);
    m_playable_units[1].push_back(second_unit);

    sf::FloatRect bounds = halo->get_sprite().getLocalBounds();
    halo->setOrigin(bounds.width / 2.f, bounds.height / 2.f);
    halo->setPosition(20, -120);
    halo->setScale({0.4, 0.4});
    m_active_unit->attach_child(std::move(halo));
    m_camera = Camera(m_active_unit->get_body().get_position(), 2);
    m_camera.set_follow_strategy(std::make_unique<SmoothFollowStrategy>(&m_camera, m_active_unit, .5f, 3.f));
    std::unique_ptr<Map> map = std::make_unique<Map>(
        *this,
        std::vector<std::vector<std::pair<float, float>>> {generate_naive_map()}
    );
    m_map = map.get();
    m_scene_layers[MAP]->attach_child(std::move(map));

    auto bazooka = std::make_unique<Bazooka>(*this, m_active_unit);
    m_active_unit->attach_child(std::move(bazooka));
}

void World::draw() {
    m_world_view = m_context.window->getDefaultView();
    m_world_view.setCenter(m_camera.get_offset() * SCALE);
    m_world_view.zoom(m_camera.get_zoom());
    m_context.window->setView(m_world_view);
    m_context.window->draw(m_scene_graph);
}

void World::update(sf::Time delta_time) {
    m_moves_timer -= delta_time.asSeconds();
    if (m_moves_timer <= 0) {
        m_event_manager->queue_event(
                std::make_unique<MoveTransitionEventData>(MoveTransitionEventData::TransitionType::OTHER_PLAYER));
        m_moves_timer = 5;
    }
    m_event_manager->update();
    m_physics_world.Step(delta_time.asSeconds(), 1, 1);
    m_scene_graph.update(delta_time);
    m_camera.update(delta_time);
    m_collision_listener->reset();
    m_destruction_listener->reset();
    m_camera.set_follow_strategy(std::make_unique<SmoothFollowStrategy>(&m_camera, m_active_unit, .5f, 3.f));
}

void World::add_entity(std::unique_ptr<Entity> ptr) {
    m_scene_layers[ENTITIES]->attach_child(std::move(ptr));
}

void World::activate_next_unit() {
    m_last_active_units[m_current_player]++;
    m_last_active_units[m_current_player] %= m_playable_units[m_current_player].size();
    m_active_unit = m_playable_units[m_current_player][m_last_active_units[m_current_player]];
}

void World::activate_next_player() {
    while (m_playable_units[(++m_current_player) % m_players_number].empty()) {}
    m_current_player %= m_players_number;
    activate_next_unit();
}

void World::remove_playable_unit(int player_id, Unit *unit) {
    auto deleted_object = std::find(m_playable_units[player_id].begin(), m_playable_units[player_id].end(), unit);
    if (deleted_object != m_playable_units[player_id].end()) {
        m_playable_units[player_id].erase(deleted_object);
        m_units_number--;
    }
    if (m_units_number == 0) {
        m_event_manager->queue_event(std::make_unique<GameOverEventData>());
    }
}
