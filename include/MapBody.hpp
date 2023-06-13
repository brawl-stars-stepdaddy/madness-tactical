#ifndef MAP_BODY_HPP_
#define MAP_BODY_HPP_

#include <box2d/box2d.h>
#include <clipper2/clipper.h>
#include <SFML/Graphics.hpp>
#include "Body.hpp"
#include "Explosion.hpp"
#include <opencv2/imgproc.hpp>

struct Map;

struct MapBody : Body {
public:
    explicit MapBody(Map *, b2World &, std::vector<std::vector<cv::Point>> &&, std::vector<cv::Vec4i> &&);

    [[nodiscard]] std::vector<sf::ConvexShape> get_triangulation() const;

    void apply_explosion(const Explosion &);

    void process_contours(std::vector<std::vector<cv::Point>> &, std::vector<cv::Vec4i> &);

    sf::Vector2f get_position() override;
    float get_rotation() override;

private:
    std::vector<std::vector<cv::Point2f>> m_contours;
    std::vector<std::vector<b2Vec2>> m_chains;
    Clipper2Lib::PathsD m_paths;
};

#endif