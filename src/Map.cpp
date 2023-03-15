#include <Map.hpp>

Map::Map(b2World *world, const std::vector<std::vector<std::pair<float, float>>> &chains_) {
    b2BodyDef map_def;
    map_def.position.Set(0.0f, 0.0f);
    body = world->CreateBody(&map_def);

    b2ChainShape map_shape;
    b2FixtureDef map_fixture;
    map_fixture.friction = 1.0f;

    for (const auto &chain: chains_) {
        chains.emplace_back();
        paths.emplace_back();
        chains.back().reserve(chain.size());
        paths.back().reserve(chain.size());

        for (const auto &[x, y]: chain) {
            paths.back().emplace_back(x, y);
            chains.back().emplace_back(x, y);
        }

        map_shape.Clear();
        map_shape.CreateLoop(chains.back().data(), static_cast<int>(chains.back().size()));
        map_fixture.shape = &map_shape;
        body->CreateFixture(&map_fixture);
    }
}

[[nodiscard]] std::vector<sf::ConvexShape> Map::get_triangulation() const {
    std::vector<sf::ConvexShape> sf_triangles;

    TPPLPartition triangulator;
    TPPLPolyList polygons, triangles;

    for (const auto &chain : chains) {
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

void Map::apply_explosion(const Explosion &explosion) {
    auto [x_explosion, y_explosion] = explosion.get_coordinates();
    float radius = explosion.get_radius();

    Clipper2Lib::PathsD explosion_area({Clipper2Lib::Ellipse<double>({x_explosion, y_explosion}, radius, radius, 20)});
    paths = Clipper2Lib::Difference(paths, explosion_area, Clipper2Lib::FillRule::EvenOdd);

    chains.clear();
    auto fixture = body->GetFixtureList();
    while (fixture) {
        auto old_fixture = fixture;
        fixture = fixture->GetNext();
        body->DestroyFixture(old_fixture);
    }

    b2ChainShape map_shape;
    b2FixtureDef map_fixture;
    map_fixture.friction = 1.0f;

    for (const auto &path: paths) {
        chains.emplace_back();
        chains.back().reserve(path.size());

        for (const auto &[x, y]: path) {
            chains.back().emplace_back(x, y);
        }

        map_shape.Clear();
        map_shape.CreateLoop(chains.back().data(), static_cast<int>(chains.back().size()));
        map_fixture.shape = &map_shape;
        body->CreateFixture(&map_fixture);
    }

    // TODO: graphical part
}
