#include <polypartition.h>
#include "MapBody.hpp"

MapBody::MapBody(b2World &world, const std::vector<std::vector<std::pair<float, float>>> &chains_) {
    b2BodyDef map_def;
    map_def.position.Set(0.0f, 0.0f);
    m_body = world.CreateBody(&map_def);

    b2ChainShape map_shape;
    b2FixtureDef map_fixture;
    map_fixture.friction = 1.0f;

    for (const auto &chain: chains_) {
        m_chains.emplace_back();
        m_paths.emplace_back();
        m_chains.back().reserve(chain.size());
        m_paths.back().reserve(chain.size());

        for (const auto &[x, y]: chain) {
            m_paths.back().emplace_back(x, y);
            m_chains.back().emplace_back(x, y);
        }

        map_shape.Clear();
        map_shape.CreateLoop(m_chains.back().data(), static_cast<int>(m_chains.back().size()));
        map_fixture.shape = &map_shape;
        m_body->CreateFixture(&map_fixture);
    }
}

sf::Vector2f MapBody::get_position() {
    return {0, 0};
}

float MapBody::get_rotation() {
    return 0;
}

[[nodiscard]] std::vector<sf::ConvexShape> MapBody::get_triangulation() const {
    std::vector<sf::ConvexShape> sf_triangles;

    TPPLPartition triangulator;
    TPPLPolyList polygons, triangles;

    for (const auto &chain : m_chains) {
        TPPLPoly polygon;
        polygon.Init(static_cast<long>(chain.size()));
        for (int i = 0; i < chain.size(); i++) {
            polygon[i] = {chain[i].x, chain[i].y};
        }
        if (polygon.GetOrientation() == TPPLOrientation::TPPL_ORIENTATION_CW) {
            polygon.SetHole(true);
        }
        polygons.push_back(polygon);
    }

    triangulator.Triangulate_EC(&polygons, &triangles);
    auto triangles_ = triangles;
    triangulator.RemoveHoles(&triangles_, &triangles);

    for (const auto &triangle: triangles) {
        sf::ConvexShape sf_triangle;
        sf_triangle.setPointCount(3);
        for (int i = 0; i < 3; i++) {
            sf_triangle.setPoint(i, {static_cast<float>(triangle[i].x), static_cast<float>(triangle[i].y)});
        }
        sf_triangles.push_back(sf_triangle);
    }

    return sf_triangles;
}

void MapBody::apply_weapon_effect(const WeaponEffect &weapon_effect) {
    auto [x_explosion, y_explosion] = weapon_effect.get_coordinates();
    float radius = weapon_effect.get_radius();

    Clipper2Lib::PathsD explosion_area({Clipper2Lib::Ellipse<double>({x_explosion, y_explosion}, radius, radius, 20)});
    m_paths = Clipper2Lib::Difference(m_paths, explosion_area, Clipper2Lib::FillRule::EvenOdd);

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

    for (const auto &path: m_paths) {
        m_chains.emplace_back();
        m_chains.back().reserve(path.size());

        for (const auto &[x, y]: path) {
            m_chains.back().emplace_back(x, y);
        }

        map_shape.Clear();
        map_shape.CreateLoop(m_chains.back().data(), static_cast<int>(m_chains.back().size()));
        map_fixture.shape = &map_shape;
        m_body->CreateFixture(&map_fixture);
    }
}
