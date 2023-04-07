#include "box2d/box2d.h"
#include "SFML/Graphics.hpp"
#include "Map.hpp"
#include "Character.hpp"
#include "WeaponEffect.hpp"

const float SCALE = 100.f;
const float DEG  =  -57.29577f;

struct Ball {};

int main() {
    b2Vec2 gravity(0.0f, -10.0f);
    b2World world(gravity);

    std::vector<std::vector<std::pair<float, float>>> points;

    points.emplace_back();
    points.back().emplace_back(3, 2);
    points.back().emplace_back(7, 2);
    points.back().emplace_back(7, 3);
    points.back().emplace_back(6, 3);
    points.back().emplace_back(4, 3);
    points.back().emplace_back(3, 3);


    auto map = std::make_unique<Map>(&world, points);

    std::vector<sf::ConvexShape> sf_triangles = map->get_body().get_triangulation();
    for (auto &triangle: sf_triangles) {
        for (int i = 0; i < 3; i++) {
            triangle.setPoint(i, {triangle.getPoint(i).x * SCALE, 500 - triangle.getPoint(i).y * SCALE});
        }
        triangle.setFillColor(sf::Color(136, 69, 19));
        triangle.setOutlineThickness(1);
        triangle.setOutlineColor(sf::Color(61, 12, 2));
    }

    auto worm = std::make_unique<Character>(&world, 500, 800);


    /*
    b2BodyDef bodyDef;
    bodyDef.type = b2_dynamicBody;
    bodyDef.position.Set(5.0f, 3.5f);

    Ball ball = Ball();
    Ball *ball_ptr = &ball;
    bodyDef.userData.pointer = reinterpret_cast<uintptr_t>(ball_ptr);

    m_body *m_body = world.CreateBody(&bodyDef);
    b2CircleShape dynamicCircle;
    dynamicCircle.m_radius = 0.2f;
    b2FixtureDef fixtureDef;
    fixtureDef.shape = &dynamicCircle;
    fixtureDef.density = 1.0f;
    fixtureDef.friction = 1.0f;
    fixtureDef.restitution = 0.5f;
    m_body->CreateFixture(&fixtureDef);
     */

    float timeStep = 1.0f / 60.0f;
    int32 velocityIterations = 6;
    int32 positionIterations = 2;

    sf::RenderWindow window(sf::VideoMode(1000, 500), "Physics Test");
    window.setFramerateLimit(60);

//    sf::Texture football_texture;
//    football_texture.loadFromFile("../assets/football.jpg");
//    football_texture.setSmooth(true);
//
//    sf::CircleShape s_circle(20);
//    s_circle.setTexture(&football_texture);
//    s_circle.setOrigin(20, 20);
//    s_circle.setPosition(500, 150);

/*    sf::RectangleShape s_ground({500, 100});
    s_ground.setFillColor(sf::Color(136, 69, 19));
    s_ground.setOutlineThickness(5);
    s_ground.setOutlineColor(sf::Color(61,12,2));
    s_ground.setOrigin(250, 50);
    s_ground.setPosition(500, 250);*/

    std::vector<sf::CircleShape> holes;

    auto map_ptr = map.get();
    auto worm_ptr = worm.get();

    auto scene_node = std::make_unique<SceneNode>();
    scene_node->attach_child(std::move(map));
    scene_node->attach_child(std::move(worm));

    while (window.isOpen()) {
        sf::Event e{};
        while (window.pollEvent(e)) {
            if (e.type == sf::Event::Closed)
                window.close();

            if (e.type == sf::Event::MouseButtonPressed) {
                if (e.mouseButton.button == sf::Mouse::Left) {
                    auto [x_, y_] = sf::Mouse::getPosition(window);

                    float x = static_cast<float>(x_) / SCALE;
                    float y = static_cast<float>(500 - y_) / SCALE;

                    WeaponEffect explosion({x, y}, 0.5, WeaponEffect::WeaponEffectType::Explosion);
                    map_ptr->apply_weapon_effect(explosion);
                    worm_ptr->apply_weapon_effect(explosion);


                    sf::CircleShape new_hole;
                    new_hole.setRadius(50);
                    new_hole.setOrigin(50, 50);
                    new_hole.setPosition(x_, y_);
                    new_hole.setFillColor(sf::Color(0, 0, 0));
                    holes.push_back(new_hole);
                }
            }
        }

        world.Step(timeStep, velocityIterations, positionIterations);

        window.clear();

        for (const auto &tr: sf_triangles) {
            window.draw(tr);
        }

        for (const auto &hole: holes) {
            window.draw(hole);
        }

        for (b2Body *it = world.GetBodyList(); it != nullptr; it = it->GetNext()) {
            b2Vec2 pos = it->GetPosition();
            float angle = it->GetAngle();
            if (it->GetUserData().pointer == reinterpret_cast<uintptr_t>(ball_ptr)) {
                s_circle.setPosition(pos.x * SCALE, 500 - pos.y * SCALE);
                s_circle.setRotation(angle * DEG);
                window.draw(s_circle);
            }
        }

        window.display();
    }
/*
#include "PhysicsTest.hpp"
#include "Game.hpp"

int main() {
    Game().run();
    return 0;
*/
}
