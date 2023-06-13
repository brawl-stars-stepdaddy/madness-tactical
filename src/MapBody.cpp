#include "MapBody.hpp"
#include <CDT.h>
#include "clipper2/clipper.h"
#include <set>

MapBody::MapBody(
    Map *parent,
    b2World &world,
    std::vector<std::vector<cv::Point>> &&contours,
    std::vector<cv::Vec4i> &&hierarchy
) {
    b2BodyDef map_def;
    map_def.position.Set(0.0f, 0.0f);
    map_def.userData.pointer = reinterpret_cast<uintptr_t>(parent);
    m_body = world.CreateBody(&map_def);

    b2ChainShape map_shape;
    b2FixtureDef map_fixture;
    map_fixture.friction = 0.5f;

    process_contours(contours, hierarchy);

    for (const auto &chain : m_contours) {
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
}

sf::Vector2f MapBody::get_position() {
    return {0, 0};
}

float MapBody::get_rotation() {
    return 0;
}

[[nodiscard]] std::vector<sf::ConvexShape> MapBody::get_triangulation() const {

    std::vector<sf::ConvexShape> sf_triangles;

    CDT::Triangulation<double> cdt;
    std::vector<CDT::V2d<double>> vertices;
    std::vector<CDT::Edge> edges;

    int index = 0;
    for (int j = 0; j < m_contours.size(); j++) {
        const auto &contour = m_contours[j];
        for (int i = 0; i < contour.size(); i++) {
            vertices.emplace_back(CDT::V2d<double>::make(contour[i].x, contour[i].y));
            edges.emplace_back(index + i, index + (i + 1) % contour.size());
        }
        index += contour.size();
    }

    cdt.insertVertices(vertices);
    cdt.insertEdges(edges);
    cdt.eraseOuterTrianglesAndHoles();

    for (const auto &cdt_triangle: cdt.triangles) {
        sf::ConvexShape sf_triangle;
        sf_triangle.setPointCount(3);
        for (int i = 0; i < 3; i++) {
            auto point = vertices[cdt_triangle.vertices[i]];
            sf_triangle.setPoint(i, {static_cast<float>(point.x), static_cast<float>(point.y)});
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

bool check_collinear(cv::Point2f first, cv::Point2f second, cv::Point2f third) {
    auto [x1, y1] = first;
    auto [x2, y2] = second;
    auto [x3, y3] = third;
    float dx1 = x2 - x1;
    float dy1 = y2 - y1;
    float dx2 = x3 - x2;
    float dy2 = y3 - y2;
    return abs(dx1 / dy1 - dx2 / dy2) > 1e-6;

}

void MapBody::process_contours(std::vector<std::vector<cv::Point>> &contours, std::vector<cv::Vec4i> &hierarchy) {
    std::set<std::pair<int, int>> used;

    for (int j = 0; j < contours.size(); j++) {
        auto contour = contours[j];
        if (contour.size() < 100) {
            continue;
        }

        int level = 0, index = j;
        while (hierarchy[index][3] != -1) {
            level++;
            index = hierarchy[index][3];
        }
        if (level >= 2) {
            continue;
        }

        m_contours.emplace_back();
        int i = 0;
        for (const auto &[row, col] : contour) {
            if (i++ % 2 || used.find({row, col}) != used.end()) {
                continue;
            }
            used.insert({row, col});
            float x = static_cast<float>(col - 500) / 10;
            float y = static_cast<float>(row - 500) / 10;
            if (m_contours.back().size() < 2
                || check_collinear(m_contours.back()[m_contours.back().size() - 2], m_contours.back()[m_contours.back().size()- 1], cv::Point2f(x, y))) {
                m_contours.back().emplace_back(x, y);
            }
        }
    }
}
