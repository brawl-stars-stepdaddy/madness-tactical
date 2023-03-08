#include "box2d/box2d.h"
#include "SFML/Graphics.hpp"
#include "clipper2/clipper.h"
#include "poly2tri/poly2tri.h"
#include <cstdio>

const float SCALE = 30.f;
const float DEG  =  -57.29577f;

struct Ball {};

// Convert Box2D chains to ClipperLib::IntPoint
Clipper2Lib::PathsD b2VerticesToClipper(const b2Vec2* vertices, int count) {
    Clipper2Lib::PathsD result;
    Clipper2Lib::PathD tmp;
    tmp.reserve(count);

    for (int i = 0; i < count; ++i)
    {
        const auto x = vertices[i].x;
        const auto y = vertices[i].y;
        tmp.emplace_back(x, y);
    }
    result.push_back(tmp);
    return result;
}

int main() {
    b2Vec2 gravity(0.0f, -10.0f);
    b2World world(gravity);

    std::vector<p2t::Point*> points_inv;
    points_inv.push_back(new p2t::Point(700, 100));
    points_inv.push_back(new p2t::Point(700, 300));
    points_inv.push_back(new p2t::Point(500, 280));
    points_inv.push_back(new p2t::Point(300, 300));
    points_inv.push_back(new p2t::Point(300, 100));

    std::vector<p2t::Point*> points;
    points.push_back(new p2t::Point(300, 100));
    points.push_back(new p2t::Point(300, 300));
    points.push_back(new p2t::Point(500, 280));
    points.push_back(new p2t::Point(700, 300));
    points.push_back(new p2t::Point(700, 100));


    std::vector<p2t::Point*> hole_points;
    hole_points.push_back(new p2t::Point(400, 150));
    hole_points.push_back(new p2t::Point(400, 250));
    hole_points.push_back(new p2t::Point(600, 250));
    hole_points.push_back(new p2t::Point(600, 150));

    std::vector<p2t::Point*> hole2_points;
    hole2_points.push_back(new p2t::Point(450, 175));
    hole2_points.push_back(new p2t::Point(450, 225));
    hole2_points.push_back(new p2t::Point(550, 225));
    hole2_points.push_back(new p2t::Point(550, 175));

    auto cdt = p2t::CDT(points_inv);
    auto cdt2 = p2t::CDT(hole2_points);
    cdt.AddHole(hole_points);
    cdt.Triangulate();
    cdt2.Triangulate();

// Don't forget to free the memory allocated for the CDT and its triangles

    std::vector<sf::ConvexShape> sf_triangles;
    for (const auto& triangle : cdt.GetTriangles()) {
        sf::ConvexShape tr;
        tr.setPointCount(3);
        p2t::Point* p1 = triangle->GetPoint(0);
        p2t::Point* p2 = triangle->GetPoint(1);
        p2t::Point* p3 = triangle->GetPoint(2);
        tr.setPoint(0, {static_cast<float>(p1->x), static_cast<float>(500 - p1->y)});
        tr.setPoint(1, {static_cast<float>(p2->x), static_cast<float>(500 - p2->y)});
        tr.setPoint(2, {static_cast<float>(p3->x), static_cast<float>(500 - p3->y)});
        tr.setFillColor(sf::Color(136, 69, 19));
        tr.setOutlineThickness(5);
        tr.setOutlineColor(sf::Color(61,12,2));
        sf_triangles.push_back(tr);
    }
    for (const auto& triangle : cdt2.GetTriangles()) {
        sf::ConvexShape tr;
        tr.setPointCount(3);
        p2t::Point* p1 = triangle->GetPoint(0);
        p2t::Point* p2 = triangle->GetPoint(1);
        p2t::Point* p3 = triangle->GetPoint(2);
        tr.setPoint(0, {static_cast<float>(p1->x), static_cast<float>(500 - p1->y)});
        tr.setPoint(1, {static_cast<float>(p2->x), static_cast<float>(500 - p2->y)});
        tr.setPoint(2, {static_cast<float>(p3->x), static_cast<float>(500 - p3->y)});
        tr.setFillColor(sf::Color(136, 69, 19));
        tr.setOutlineThickness(5);
        tr.setOutlineColor(sf::Color(61,12,2));
        sf_triangles.push_back(tr);
    }

    b2ChainShape containing_box_shape;
    std::vector<b2Vec2> corners(4);
    corners[0] = b2Vec2(0.0f / SCALE, 0.0f / SCALE);
    corners[1] = b2Vec2(0.0f / SCALE, 500.0f / SCALE);
    corners[2] = b2Vec2(1000.0f / SCALE, 500.0f / SCALE);
    corners[3] = b2Vec2(1000.0f / SCALE, 0.0f / SCALE);
    containing_box_shape.CreateLoop(corners.data(), 4);

    b2BodyDef containing_box;
    containing_box.position.Set(0.0f / SCALE, 0.0f / SCALE);
    b2Body* containing_body = world.CreateBody(&containing_box);
    b2FixtureDef containing_fixture;
    containing_fixture.shape = &containing_box_shape;
    containing_fixture.friction = 1.0f;
    containing_body->CreateFixture(&containing_fixture);


    b2ChainShape ground_box_shape;
    b2Vec2 ground_chain[1000];
    int cnt = 0;
    for (auto &point : points_inv) {
        ground_chain[cnt++] = b2Vec2(point->x / SCALE, point->y / SCALE);
    }
    int ground_chain_size = cnt;
    ground_box_shape.CreateLoop(ground_chain, cnt);

    b2BodyDef ground_box;
    ground_box.position.Set(0.0f / SCALE, 0.0f / SCALE);
    b2Body* ground_body = world.CreateBody(&ground_box);
    b2FixtureDef ground_fixture;
    ground_fixture.shape = &ground_box_shape;
    ground_fixture.friction = 1.0f;
    ground_body->CreateFixture(&ground_fixture);

    b2ChainShape ground_box_shape2;
    b2Vec2 ground_chain2[1000];
    int cnt2 = 0;
    for (auto &point : points) {
        ground_chain2[cnt2++] = b2Vec2(point->x / SCALE, point->y / SCALE);
    }
    int ground_chain_size2 = cnt2;
    ground_box_shape2.CreateLoop(ground_chain2, cnt2);

    b2BodyDef ground_box2;
    ground_box2.position.Set(0.0f / SCALE, 0.0f / SCALE);
    b2FixtureDef ground_fixture2;
    ground_fixture2.shape = &ground_box_shape2;
    ground_fixture2.friction = 1.0f;
    ground_body->CreateFixture(&ground_fixture2);


    b2BodyDef bodyDef;
    bodyDef.type = b2_dynamicBody;
    bodyDef.position.Set(500.0f / SCALE, 400.0f / SCALE);

    Ball ball = Ball();
    Ball* ball_ptr = &ball;
    bodyDef.userData.pointer = reinterpret_cast<uintptr_t>(ball_ptr);

    b2Body* body = world.CreateBody(&bodyDef);
    b2CircleShape dynamicCircle;
    dynamicCircle.m_radius = 30.0f / SCALE;
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

    sf::CircleShape s_circle(30);
    s_circle.setTexture(&football_texture);
    s_circle.setOrigin(30, 30);
    s_circle.setPosition(500, 100);

/*    sf::RectangleShape s_ground({500, 100});
    s_ground.setFillColor(sf::Color(136, 69, 19));
    s_ground.setOutlineThickness(5);
    s_ground.setOutlineColor(sf::Color(61,12,2));
    s_ground.setOrigin(250, 50);
    s_ground.setPosition(500, 250);*/

    std::vector<sf::CircleShape> black_circles;

    while (window.isOpen()) {

        sf::Event e{};
        while (window.pollEvent(e))
        {
            if (e.type == sf::Event::Closed)
                window.close();

            if (e.type == sf::Event::MouseButtonPressed)
            {
                if (e.mouseButton.button == sf::Mouse::Left)
                {
                    auto [x, y] = sf::Mouse::getPosition(window);
                    sf::CircleShape b_circle(30);
                    b_circle.setFillColor(sf::Color(0, 0, 0));
                    b_circle.setOrigin(30, 30);
                    b_circle.setPosition(x, y);
                    black_circles.push_back(b_circle);

                    Clipper2Lib::PathsD subject =
                            b2VerticesToClipper(ground_chain, ground_chain_size);
                    Clipper2Lib::PathsD clip_circle({Clipper2Lib::Ellipse<double>({x / SCALE, (500 - y) / SCALE}, 30 / SCALE, 30 / SCALE, 20)});
                    Clipper2Lib::PathsD tmp, solution;
                    Clipper2Lib::FillRule fr = Clipper2Lib::FillRule::NonZero;
                    solution = Clipper2Lib::Difference(subject, clip_circle, fr);

                    Clipper2Lib::PathD new_chain = solution.front();

                    world.DestroyBody(ground_body);

                    cnt = 0;
                    for (auto &point : new_chain) {
                        ground_chain[cnt++] = b2Vec2(point.x, point.y);
                    }
                    ground_chain_size = cnt;
                    ground_box_shape.Clear();
                    ground_box_shape.CreateLoop(ground_chain, ground_chain_size);

                    ground_box.position.Set(0.0f / SCALE, 0.0f / SCALE);
                    ground_body = world.CreateBody(&ground_box);
                    ground_fixture.shape = &ground_box_shape;
                    ground_fixture.friction = 1.0f;
                    ground_body->CreateFixture(&ground_fixture);
                }
            }
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
            body->ApplyForceToCenter(b2Vec2(100, 0), true);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
            body->ApplyForceToCenter(b2Vec2(-100, 0), true);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
            body->ApplyForceToCenter(b2Vec2(0, 100), true);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
            body->ApplyForceToCenter(b2Vec2(0, -100), true);
        }



        world.Step(timeStep, velocityIterations, positionIterations);

        window.clear();

       // window.draw(s_ground);

       for (const auto& tr : sf_triangles) {
           window.draw(tr);
       }

        for (const auto& b : black_circles) {
            window.draw(b);
        }

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