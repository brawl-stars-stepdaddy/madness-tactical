#ifndef MAP_GENERATOR_HPP_
#define MAP_GENERATOR_HPP_

#include <vector>

struct MapGenerator {
    MapGenerator(int map_size, int octaves = 1,
                 float simplex_scale = 0.008f, float threshold = 3.0f,
                 float scale = 5.0f, int points_frequency = 3);
    const std::vector<std::vector<std::pair<float, float>>> &get_chains();

private:
    void figure_bfs(std::pair<int, int> position, bool target);
    bool contour_dfs(std::pair<int, int> position, std::pair<int, int> start_position);
    void process_contours();

    int m_map_size;
    float m_scale;
    int m_points_frequency;
    std::vector<std::vector<bool>> m_noise_map, m_figures_map, m_contours_map;
    std::vector<std::pair<int, int>> m_contour_points;
    std::vector<std::vector<std::pair<int, int>>> m_contours;
    std::vector<std::vector<std::pair<float, float>>> m_chains;

    const std::vector<std::pair<int, int>> m_moves_4 = {
        {-1, 0}, {0, -1}, {1, 0}, {0, 1}
    };

    const std::vector<std::pair<int, int>> m_moves_8 = {
            {-1, 0}, {0, -1}, {1, 0}, {0, 1},
            {-1, -1}, {1, -1}, {-1, 1}, {1, 1}
    };
};

#endif // MAP_GENERATOR_HPP_
