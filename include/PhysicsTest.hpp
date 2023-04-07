#ifndef PHYSICSTEST_HPP_
#define PHYSICSTEST_HPP_

#include "Explosion.hpp"
#include "Map.hpp"
#include "SFML/Graphics.hpp"
#include "box2d/box2d.h"

struct PhysicsTest {
    const float SCALE = 100.f;
    const float DEG = -57.29577f;

    struct Ball {};

    void run() {
        b2Vec2 gravity(0.0f, -10.0f);
        b2World world(gravity);

        std::vector<std::vector<std::pair<float, float>>> points;

        points.emplace_back();
        points.back().emplace_back(0, 0);
        points.back().emplace_back(10, 0);
        points.back().emplace_back(10, 5);
        points.back().emplace_back(0, 5);

        points.emplace_back();
        points.back().emplace_back(1, 1.9);
        points.back().emplace_back(1, 4);
        points.back().emplace_back(9, 4);
        points.back().emplace_back(9, 1.9);

        points.emplace_back();
        points.back().emplace_back(3, 2);
        points.back().emplace_back(7, 2);
        points.back().emplace_back(7, 3);
        points.back().emplace_back(6, 3);
        points.back().emplace_back(4, 3);
        points.back().emplace_back(3, 3);

        points.emplace_back();
        points.back().emplace_back(6, 2.75);
        points.back().emplace_back(6.5, 2.75);
        points.back().emplace_back(6.5, 2.25);
        points.back().emplace_back(3.5, 2.25);
        points.back().emplace_back(3.5, 2.75);
        points.back().emplace_back(4, 2.75);

        Map map(&world, points);

        std::vector<sf::ConvexShape> sf_triangles = map.get_triangulation();
        for (auto &triangle : sf_triangles) {
            for (int i = 0; i < 3; i++) {
                triangle.setPoint(
                    i, {triangle.getPoint(i).x * SCALE,
                        500 - triangle.getPoint(i).y * SCALE}
                );
            }
            triangle.setFillColor(sf::Color(136, 69, 19));
            triangle.setOutlineThickness(1);
            triangle.setOutlineColor(sf::Color(61, 12, 2));
        }

        b2BodyDef bodyDef;
        bodyDef.type = b2_dynamicBody;
        bodyDef.position.Set(5.0f, 3.5f);

        Ball ball = Ball();
        Ball *ball_ptr = &ball;
        bodyDef.userData.pointer = reinterpret_cast<uintptr_t>(ball_ptr);

        b2Body *body = world.CreateBody(&bodyDef);
        b2CircleShape dynamicCircle;
        dynamicCircle.m_radius = 0.2f;
        b2FixtureDef fixtureDef;
        fixtureDef.shape = &dynamicCircle;
        fixtureDef.density = 1.0f;
        fixtureDef.friction = 1.0f;
        fixtureDef.restitution = 0.5f;
        body->CreateFixture(&fixtureDef);

        float timeStep = 1.0f / 60.0f;
        int32 velocityIterations = 6;
        int32 positionIterations = 2;

        sf::RenderWindow window(sf::VideoMode(1000, 500), "Physics Test");
        window.setFramerateLimit(60);

        sf::Texture football_texture;
        football_texture.loadFromFile("res/Engineer.jpg");
        football_texture.setSmooth(true);

        sf::CircleShape s_circle(60);
        s_circle.setTexture(&football_texture);
        s_circle.setOrigin(60, 60);
        s_circle.scale({1, -1});
        s_circle.setPosition(500, 150);

        /*    sf::RectangleShape s_ground({500, 100});
            s_ground.setFillColor(sf::Color(136, 69, 19));
            s_ground.setOutlineThickness(5);
            s_ground.setOutlineColor(sf::Color(61,12,2));
            s_ground.setOrigin(250, 50);
            s_ground.setPosition(500, 250);*/

        std::vector<sf::CircleShape> holes;

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

                        Explosion explosion({x, y}, 0.5);
                        map.apply_explosion(explosion);

                        sf::CircleShape new_hole;
                        new_hole.setRadius(50);
                        new_hole.setOrigin(50, 50);
                        new_hole.setPosition(x_, y_);
                        new_hole.setFillColor(sf::Color(0, 0, 0));
                        holes.push_back(new_hole);
                    }
                }
            }

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
                body->ApplyForceToCenter(b2Vec2(3, 0), true);
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
                body->ApplyForceToCenter(b2Vec2(-3, 0), true);
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
                body->ApplyForceToCenter(b2Vec2(0, 3), true);
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
                body->ApplyForceToCenter(b2Vec2(0, -3), true);
            }

            world.Step(timeStep, velocityIterations, positionIterations);

            window.clear();

            for (const auto &tr : sf_triangles) {
                window.draw(tr);
            }

            for (const auto &hole : holes) {
                window.draw(hole);
            }

            for (b2Body *it = world.GetBodyList(); it != nullptr;
                 it = it->GetNext()) {
                b2Vec2 pos = it->GetPosition();
                float angle = it->GetAngle();
                if (it->GetUserData().pointer ==
                    reinterpret_cast<uintptr_t>(ball_ptr)) {
                    s_circle.setPosition(pos.x * SCALE, 500 - pos.y * SCALE);
                    s_circle.setRotation(angle * DEG);
                    window.draw(s_circle);
                }
            }

            window.display();
        }
    }
};

#endif
