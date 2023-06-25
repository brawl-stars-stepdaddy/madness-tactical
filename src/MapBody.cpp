#include "MapBody.hpp"
#include <CDT.h>
#include "clipper2/clipper.h"

MapBody::MapBody(
    Map *parent,
    b2World &world,
    const std::vector<std::vector<std::pair<float, float>>> &chains
) {
    b2BodyDef map_def;
    map_def.position.Set(0.0f, 0.0f);
    map_def.userData.pointer = reinterpret_cast<uintptr_t>(parent);
    m_body = world.CreateBody(&map_def);

    b2ChainShape map_shape;
    b2FixtureDef map_fixture;
    map_fixture.friction = 1.0f;

    for (const auto &chain : chains) {
        m_chains.emplace_back();
        m_paths.emplace_back();
        m_chains.back().reserve(chain.size());
        m_paths.back().reserve(chain.size());

        for (const auto &[x, y] : chain) {
            m_paths.back().emplace_back(x, y);
            m_chains.back().emplace_back(x, y);
        }

        map_shape.Clear();
        map_shape.CreateLoop(
            m_chains.back().data(), static_cast<int>(m_chains.back().size())
        );
        map_fixture.shape = &map_shape;
        m_body->CreateFixture(&map_fixture);
    }

    apply_explosion(Explosion({0, 0}, 0));
}

sf::Vector2f MapBody::get_position() const {
    return {0, 0};
}

float MapBody::get_rotation() const {
    return 0;
}

[[nodiscard]] std::vector<sf::ConvexShape> MapBody::get_triangulation() const {
    std::vector<sf::ConvexShape> sf_triangles;

    CDT::Triangulation<double> cdt;
    std::vector<CDT::V2d<double>> vertices;
    std::vector<CDT::Edge> edges;

    int index = 0;
    for (const auto &chain : m_chains) {
        for (int i = 0; i < chain.size(); i++) {
            vertices.emplace_back(CDT::V2d<double>::make(chain[i].x, chain[i].y)
            );
            edges.emplace_back(index + i, index + (i + 1) % chain.size());
        }
        index += chain.size();
    }

    cdt.insertVertices(vertices);
    cdt.insertEdges(edges);
    cdt.eraseOuterTrianglesAndHoles();

    for (const auto &cdt_triangle : cdt.triangles) {
        sf::ConvexShape sf_triangle;
        sf_triangle.setPointCount(3);
        for (int i = 0; i < 3; i++) {
            auto point = vertices[cdt_triangle.vertices[i]];
            sf_triangle.setPoint(
                i, {static_cast<float>(point.x), static_cast<float>(point.y)}
            );
        }
        sf_triangles.push_back(sf_triangle);
    }

    return sf_triangles;
}

void MapBody::apply_explosion(const Explosion &explosion) {
    auto [x_explosion, y_explosion] = explosion.get_coordinates();
    float radius = explosion.get_radius();

    Clipper2Lib::PathsD explosion_area({Clipper2Lib::Ellipse<double>(
        {x_explosion, y_explosion}, radius, radius, 20
    )});
    m_paths = Clipper2Lib::Difference(
        m_paths, explosion_area, Clipper2Lib::FillRule::EvenOdd
    );

    m_chains.clear();
    auto fixture = m_body->GetFixtureList();
    while (fixture) {
        auto old_fixture = fixture;
        fixture = fixture->GetNext();
        m_body->DestroyFixture(old_fixture);
    }

    b2ChainShape map_shape;
    b2FixtureDef map_fixture;
    map_fixture.friction = 1.0f;

    for (const auto &path : m_paths) {
        m_chains.emplace_back();
        m_chains.back().reserve(path.size());

        for (const auto &[x, y] : path) {
            m_chains.back().emplace_back(x, y);
        }

        map_shape.Clear();
        map_shape.CreateLoop(
            m_chains.back().data(), static_cast<int>(m_chains.back().size())
        );
        map_fixture.shape = &map_shape;
        m_body->CreateFixture(&map_fixture);
    }
}
