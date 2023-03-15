#include "Character.hpp"

Character::Character(b2World* world, float x, float y) {
    b2BodyDef character_def;
    character_def.position.Set(x, y);
    character_def.fixedRotation = true;
    character_def.type = b2BodyType::b2_dynamicBody;
    m_body = world->CreateBody(&character_def);

    b2PolygonShape character_body_shape, character_sensor_shape;
    character_body_shape.SetAsBox(1.0f, 2.0f);
    character_sensor_shape.SetAsBox(0.1f, 0.1f, {-2.0f, 0}, 0.0f);

    b2FixtureDef character_body_fixture, character_sensor_fixture;
    character_body_fixture.shape = &character_body_shape;
    character_body_fixture.friction = 1.0f;
    character_body_fixture.restitution = 0.5f;
    character_sensor_fixture.isSensor = true;

    m_body->CreateFixture(&character_body_fixture);
    m_body->CreateFixture(&character_sensor_fixture);

    sf::Texture texture;
    texture.loadFromFile("../assets/worm.png");
    m_sprite.setTexture(texture);
    m_sprite.setPosition(x, y);
}

void Character::draw_current(sf::RenderTarget &target, sf::RenderStates states) const {
    target.draw(m_sprite, states);
}

void Character::apply_weapon_effect(WeaponEffect &weapon_effect) {
    auto [x_effect, y_effect] = weapon_effect.get_coordinates();
    float radius = weapon_effect.get_radius();

    auto [x, y] = m_body->GetPosition();
    float distance = sqrt((x - x_effect) * (x - x_effect) + (y - y_effect) * (y - y_effect));
    if (distance < radius) {
        m_health_points -= static_cast<int>(100.0f * (1.0f - distance / radius));
    }
}

void Character::update_current(sf::Time delta_time) {
    if (m_health_points < 0) {
        m_parent->detach_child(*this);
        delete this;
        return;
    }
    auto [x, y] = m_body->GetPosition();
    m_sprite.setPosition(x, y);

    if (m_is_active) {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
            m_body->ApplyForceToCenter(b2Vec2(3, 0), true);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
            m_body->ApplyForceToCenter(b2Vec2(-3, 0), true);
        }
        if (m_is_standing && sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
            m_body->ApplyForceToCenter(b2Vec2(0, 10), true);
        }
    }
}
