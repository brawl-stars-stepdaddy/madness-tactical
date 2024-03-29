#include "utils/MapGenerator.hpp"
#include <iostream>
#include <queue>
#include <random>
#include <vector>
#include "SimplexNoise.h"

MapGenerator::MapGenerator(
    int map_size,
    int octaves,
    float simplex_scale,
    float threshold,
    float scale,
    int points_frequency
)
    : m_map_size(map_size),
      m_scale(scale),
      m_points_frequency(points_frequency) {
    const SimplexNoise simplex(simplex_scale, 1.f, 1.f, 1.f);
    m_noise_map.resize(map_size, std::vector<bool>(map_size));

    std::uniform_real_distribution<float> range(-1e4, 1e4);
    std::mt19937 rand_gen((std::random_device()()));
    float x_offset = range(rand_gen);
    float y_offset = range(rand_gen);

    for (int row = 0; row < map_size; ++row) {
        auto y = static_cast<float>(row - map_size / 2);
        for (int col = 0; col < map_size; ++col) {
            auto x = static_cast<float>(col - map_size / 2);
            float noise = simplex.fractal(octaves, x + x_offset, y + y_offset) / 2 + 0.5;
            float multiplier = powf(x * x + y * y, 0.5) / map_size;
            noise /= std::max(0.001f, multiplier);
            m_noise_map[row][col] = noise > threshold;
        }
    }

    m_figures_map.resize(map_size, std::vector<bool>(map_size));
    m_contours_map.resize(map_size, std::vector<bool>(map_size));

    figure_bfs({0, 0}, false);
    std::size_t contour_points_number = m_contour_points.size();
    for (std::size_t i = 0; i < contour_points_number; i++) {
        const auto &[x, y] = m_contour_points[i];
        if (!m_figures_map[y][x]) {
            figure_bfs({x, y}, true);
        }
    }
    for (const auto &[x, y] : m_contour_points) {
        if (m_contours_map[y][x]) {
            m_contours.emplace_back();
            if (!contour_dfs({x, y}, {x, y})) {
                m_contours.pop_back();
            }
        }
    }
    process_contours();
}

void MapGenerator::figure_bfs(std::pair<int, int> start_position, bool target) {
    std::queue<std::pair<int, int>> queue;
    queue.push(start_position);
    m_figures_map[start_position.second][start_position.first] = true;

    while (!queue.empty()) {
        auto [x_cur, y_cur] = queue.front();
        queue.pop();

        for (const auto &[dx, dy] : m_moves_4) {
            int x = x_cur + dx;
            int y = y_cur + dy;
            if (x >= 0 && x < m_map_size && y >= 0 && y < m_map_size &&
                !m_figures_map[y][x]) {
                if (m_noise_map[y][x] == target) {
                    queue.push({x, y});
                    m_figures_map[y][x] = true;
                } else {
                    m_contours_map[y][x] = true;
                    m_contour_points.emplace_back(x, y);
                }
            }
        }
    }
}

bool MapGenerator::contour_dfs(
    std::pair<int, int> position,
    std::pair<int, int> start_position
) {
    auto [x_cur, y_cur] = position;
    m_contours_map[y_cur][x_cur] = false;
    m_contours.back().emplace_back(position);

    for (const auto &[dx, dy] : m_moves_8) {
        int x = x_cur + dx;
        int y = y_cur + dy;
        if (m_contours.back().size() > 2 && std::pair(x, y) == start_position) {
            return true;
        }
        if (x >= 0 && x < m_map_size && y >= 0 && y < m_map_size &&
            m_contours_map[y][x]) {
            if (contour_dfs({x, y}, start_position)) {
                return true;
            }
        }
    }
    m_contours.back().pop_back();
    return false;
}

void MapGenerator::process_contours() {
    for (auto &contour : m_contours) {
        if (contour.size() < 100) {
            continue;
        }
        m_chains.emplace_back();
        auto &chain = m_chains.back();
        int i = 0;
        for (const auto &[row, col] : contour) {
            if (i++ % m_points_frequency != 0) {
                continue;
            }
            float x = static_cast<float>(col - m_map_size / 2) / m_scale;
            float y = static_cast<float>(row - m_map_size / 2) / m_scale;
            chain.emplace_back(x, y);
        }
    }
}

const std::vector<std::vector<std::pair<float, float>>>
    &MapGenerator::get_chains() {
    return m_chains;
}
