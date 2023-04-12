#include "World.hpp"
#include <iostream>
#include <vector>
#include <cmath>
#include "Bazooka.hpp"
#include "CollisionEventListener.hpp"
#include "DestructionEventListener.hpp"
#include "EventManager.hpp"
#include "EventType.hpp"
#include "Explosion.hpp"
#include "ExplosionEventData.hpp"
#include "ExplosionEventListener.hpp"
#include "ActionEventListener.hpp"
#include "ActionEventData.hpp"
#include "SpriteNode.hpp"
#include "WeaponBox.hpp"
#include "Unit.hpp"

std::vector<std::pair<float, float>> generate_naive_map() {
    std::vector<std::pair<float, float>> points;
    for (int i = 0; i <= 192; i++) {
        float x = static_cast<float>(i) / 10;
        points.emplace_back(x, sin(x) / 2 + 8.);
    }
    points.emplace_back(19.2, 10.8);
    points.emplace_back(0, 10.8);
    return points;
}

World::World(sf::RenderWindow &window)
    : m_window(window),
      m_world_view(window.getDefaultView()),
      m_world_bounds(0.f, 0.f, m_world_view.getSize().x / World::SCALE, m_world_view.getSize().y / World::SCALE),
      m_spawn_position(5.f, 5.f),
      m_player_engineer(nullptr),
      m_physics_world({0, 10}),
      m_map(nullptr),
      m_game_logic(this) {
    load_textures();
    build_scene();
    EventManager::get()->add_listener(
        std::make_unique<ExplosionEventListener>(), EventType::EXPLOSION
    );
    auto listener = std::make_unique<CollisionEventListener>(this);
    m_collision_listener = listener.get();
    EventManager::get()->add_listener(
        std::move(listener), EventType::COLLISION
    );
    auto destruction_listener = std::make_unique<DestructionEventListener>();
    m_destruction_listener = destruction_listener.get();
    EventManager::get()->add_listener(
        std::move(destruction_listener), EventType::DESTRUCTION
    );
    EventManager::get()->add_listener(std::make_unique<MoveRightEventListener>(&m_game_logic), EventType::MOVE_RIGHT);
    EventManager::get()->add_listener(std::make_unique<MoveLeftEventListener>(&m_game_logic), EventType::MOVE_LEFT);
    EventManager::get()->add_listener(std::make_unique<ChangeAngleUpEventListener>(&m_game_logic), EventType::CHANGE_ANGLE_UP);
    EventManager::get()->add_listener(std::make_unique<ChangeAngleDownEventListener>(&m_game_logic), EventType::CHANGE_ANGLE_DOWN);
    EventManager::get()->add_listener(std::make_unique<JumpForwardEventListener>(&m_game_logic), EventType::JUMP_FORWARD);
    EventManager::get()->add_listener(std::make_unique<JumpBackwardEventListener>(&m_game_logic), EventType::JUMP_BACKWARD);
    EventManager::get()->add_listener(std::make_unique<ChargeWeaponEventListener>(&m_game_logic), EventType::CHARGE_WEAPON);
    EventManager::get()->add_listener(
        std::make_unique<LaunchProjectileEventListener>(&m_game_logic),
        EventType::LAUNCH_PROJECTILE
    );
    EventManager::get()->queue_event(
        std::make_unique<LaunchProjectileEventData>()
    );
}

void World::load_textures() {
    m_textures.load(TexturesID::BACKGROUND, "res/bg.jpg");
    m_textures.load(TexturesID::ENGINEER, "res/Engineer.jpg");
    m_textures.load(TexturesID::HALO, "res/HaloRender.jpg");
    m_textures.load(TexturesID::MAP_TEXTURE, "res/dirt.png");
    m_textures.load(TexturesID::WORM, "res/Worm.png");
    m_textures.load(TexturesID::CANON_BALL, "res/canon_ball.png");
    m_textures.load(TexturesID::WEAPON_BOX, "res/weapon_box.png");
    m_textures.get(TexturesID::MAP_TEXTURE).setRepeated(true);
    m_textures.get(TexturesID::BACKGROUND).setRepeated(true);
}

void World::build_scene() {
    for (std::size_t i = 0; i < LAYER_COUNT; i++) {
        SceneNode::Ptr layer = std::make_unique<SceneNode>();
        m_scene_layers[i] = layer.get();
        m_scene_graph.attach_child(std::move(layer));
    }
    std::unique_ptr<SpriteNode> background_sprite =
        std::make_unique<SpriteNode>(m_textures.get(TexturesID::BACKGROUND), sf::IntRect(m_world_bounds.left * World::SCALE,
                                                                                         m_world_bounds.top * World::SCALE,
                                                                                         m_world_bounds.width * World::SCALE,
                                                                                         m_world_bounds.height * World::SCALE));
    background_sprite->setPosition(m_world_bounds.left, m_world_bounds.top);
    m_scene_layers[BACKGROUND]->attach_child(std::move(background_sprite));
    m_scene_layers[ENTITIES]->attach_child(std::make_unique<WeaponBox>(*this, sf::FloatRect(15, 1, 1.5, 1)));
    std::unique_ptr<Unit> engie =
        std::make_unique<Unit>(Unit::Type::WORM, this, sf::Vector2f{1, 1}, 1);
    m_player_engineer = engie.get();
    m_scene_layers[ENTITIES]->attach_child(std::move(engie));
    std::unique_ptr<SpriteNode> halo =
        std::make_unique<SpriteNode>(m_textures.get(TexturesID::HALO));
    sf::FloatRect bounds = halo->get_sprite().getLocalBounds();
    halo->setOrigin(bounds.width / 2.f, bounds.height / 2.f);
    halo->setPosition(20, -120);
    halo->setScale({0.4, 0.4});
    m_player_engineer->attach_child(std::move(halo));
    m_player_engineer->setRotation(1);
    b2Body *body = m_player_engineer->get_body().get_b2Body();
    // body->SetLinearVelocity({3, 0});
    // body->SetAngularVelocity(1);
    std::unique_ptr<Map> map = std::make_unique<Map>(
        this,
        std::vector<std::vector<std::pair<float, float>>> {generate_naive_map()}
    );
    m_map = map.get();
    m_scene_layers[MAP]->attach_child(std::move(map));

    auto bazooka = std::make_unique<Bazooka>(m_player_engineer);
    m_player_engineer->set_weapon(bazooka.get());
    m_scene_layers[ENTITIES]->attach_child(std::move(bazooka));
}

void World::draw() {
    m_window.setView(m_world_view);
    m_window.draw(m_scene_graph);
}

void World::update(sf::Time delta_time) {
    EventManager::get()->update();
    m_physics_world.Step(delta_time.asSeconds(), 1, 1);
    m_scene_graph.update(delta_time);
    m_collision_listener->reset();
    m_destruction_listener->reset();
}

void World::add_entity(std::unique_ptr<Entity> ptr) {
    m_scene_layers[ENTITIES]->attach_child(std::move(ptr));
}
