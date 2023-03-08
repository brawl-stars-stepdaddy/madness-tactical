#include <Map.hpp>
#include <utility>

Map::Map(b2World* world, const std::vector<std::vector<std::pair<float, float>>> &chains_) {
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

        map_shape.CreateLoop(chains.back().data(), static_cast<int>(chains.back().size()));
        map_fixture.shape = &map_shape;
        fixtures.push_back(body->CreateFixture(&map_fixture));
    }
}

[[nodiscard]] std::vector<sf::ConvexShape> Map::get_triangulation() const {
    std::vector<p2t::Point> p2t_points;
    std::vector<p2t::Point *> p2t_point_ptrs;
    std::vector<sf::ConvexShape> sf_triangles;

    for (const auto &chain: chains) {
        for (const auto &[x, y]: chain) {
            p2t_points.emplace_back(x, y);
            p2t_point_ptrs.push_back(&p2t_points.back());
        }

        auto cdt = p2t::CDT(p2t_point_ptrs);
        cdt.Triangulate();

        std::vector<p2t::Triangle *> p2t_triangles = cdt.GetTriangles();

        for (const auto &p2t_triangle: p2t_triangles) {
            sf::ConvexShape sf_triangle;
            sf_triangle.setPointCount(3);
            for (int i = 0; i < 3; i++) {
                p2t::Point *point = p2t_triangle->GetPoint(i);
                sf_triangle.setPoint(i, {static_cast<float>(point->x), static_cast<float>(point->y)});
            }
            sf_triangles.push_back(sf_triangle);
        }
    }

    return sf_triangles;
}

void Map::apply_explosion(const Explosion &explosion) {
    auto [x_explosion, y_explosion] = explosion.get_coordinates();
    float radius = explosion.get_radius();

    Clipper2Lib::PathsD explosion_area({Clipper2Lib::Ellipse<double>({x_explosion, y_explosion}, radius, radius, 20)});
    paths = Clipper2Lib::Difference(paths, explosion_area, Clipper2Lib::FillRule::NonZero);

    chains.clear();
    for (const auto &fixture: fixtures) {
        body->DestroyFixture(fixture);
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

        map_shape.CreateLoop(chains.back().data(), static_cast<int>(path.size()));
        map_fixture.shape = &map_shape;
        fixtures.push_back(body->CreateFixture(&map_fixture));
    }

    // TODO: graphical part
}
