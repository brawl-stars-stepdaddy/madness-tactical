#include "box2d/box2d.h"
#include "SFML/Graphics.hpp"
#include <cstdio>

const float SCALE = 30.f;
const float DEG  =  -57.29577f;

struct Ball {};

int main() {
    b2Vec2 gravity(0.0f, -10.0f);
    b2World world(gravity);


    b2ChainShape containing_box_shape;
    b2Vec2 corners[4];
    corners[0] = b2Vec2(0.0f / SCALE, 0.0f / SCALE);
    corners[1] = b2Vec2(0.0f / SCALE, 500.0f / SCALE);
    corners[2] = b2Vec2(1000.0f / SCALE, 500.0f / SCALE);
    corners[3] = b2Vec2(1000.0f / SCALE, 0.0f / SCALE);
    containing_box_shape.CreateLoop(corners, 4);

    b2BodyDef containing_box;
    containing_box.position.Set(0.0f / SCALE, 0.0f / SCALE);
    b2Body* containing_body = world.CreateBody(&containing_box);
    b2FixtureDef containing_fixture;
    containing_fixture.shape = &containing_box_shape;
    containing_fixture.friction = 1.0f;
    containing_body->CreateFixture(&containing_fixture);


    b2BodyDef groundBodyDef;
    groundBodyDef.position.Set(500.0f / SCALE, (500.0f - 250.0f) / SCALE);
    b2Body* groundBody = world.CreateBody(&groundBodyDef);
    b2PolygonShape groundBox;
    groundBox.SetAsBox(250.0f / SCALE, 50.0f / SCALE);
    b2FixtureDef groundFixture;
    groundFixture.shape = &groundBox;
    groundFixture.friction = 1.0f;
    groundBody->CreateFixture(&groundFixture);

    b2BodyDef bodyDef;
    bodyDef.type = b2_dynamicBody;
    bodyDef.position.Set(500.0f / SCALE, 400.0f / SCALE);

    Ball ball = Ball();
    Ball* ball_ptr = &ball;
    bodyDef.userData.pointer = reinterpret_cast<uintptr_t>(ball_ptr);

    b2Body* body = world.CreateBody(&bodyDef);
    b2CircleShape dynamicCircle;
    dynamicCircle.m_radius = 50.0f / SCALE;
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
    football_texture.loadFromFile("../assets/football.jpg");
    football_texture.setSmooth(true);

    sf::CircleShape s_circle(50);
    s_circle.setTexture(&football_texture);
    s_circle.setOrigin(50, 50);
    s_circle.setPosition(500, 100);

    sf::RectangleShape s_ground({500, 100});
    s_ground.setFillColor(sf::Color(136, 69, 19));
    s_ground.setOutlineThickness(5);
    s_ground.setOutlineColor(sf::Color(61,12,2));
    s_ground.setOrigin(250, 50);
    s_ground.setPosition(500, 250);

    while (window.isOpen()) {

        sf::Event e{};
        while (window.pollEvent(e))
        {
            if (e.type == sf::Event::Closed)
                window.close();
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
            body->ApplyForceToCenter(b2Vec2(500, 0), true);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
            body->ApplyForceToCenter(b2Vec2(-500, 0), true);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
            body->ApplyForceToCenter(b2Vec2(0, 500), true);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
            body->ApplyForceToCenter(b2Vec2(0, -500), true);
        }


        world.Step(timeStep, velocityIterations, positionIterations);

        window.clear();

        window.draw(s_ground);

        for (b2Body* it = world.GetBodyList(); it != nullptr; it = it->GetNext()) {
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

}