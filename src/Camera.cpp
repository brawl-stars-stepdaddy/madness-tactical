#include "Camera.hpp"
#include "Entity.hpp"
#include "Body.hpp"
#include "World.hpp"

SmoothFollowStrategy::SmoothFollowStrategy(Camera *camera, Entity *target, float min_speed, float convergence_factor) : m_camera(camera), m_target(target), m_min_speed(min_speed), m_convergence_factor(convergence_factor) {

}

void SmoothFollowStrategy::update(sf::Time delta_time) {
    sf::Vector2f delta_target = m_target->get_body().get_position() - m_camera->get_offset();
    sf::Vector2f delta_move = delta_target * m_convergence_factor;
    float speed = sqrt(pow(delta_move.x, 2) + pow(delta_move.y, 2));
    float target_distance = sqrt(pow(delta_target.x, 2) + pow(delta_target.y, 2));
    if (speed < m_min_speed) {
        delta_move *= m_min_speed / speed;
        speed = m_min_speed;
    }
    if (speed * delta_time.asSeconds() > target_distance) {
        delta_move *= target_distance / speed;
        speed = target_distance / delta_time.asSeconds();
    }
    m_camera->set_offset(m_camera->get_offset() + delta_move * delta_time.asSeconds());
}

Camera::Camera(std::nullptr_t) {}

Camera::Camera(sf::Vector2f offset, float zoom) : m_offset(offset), m_current_zoom(zoom), m_expected_zoom(zoom) {

}

void Camera::update(sf::Time delta_time) {
    m_follow_strategy->update(delta_time);
    float delta_zoom = m_expected_zoom - m_current_zoom;
    float zoom_speed = delta_zoom * m_zoom_convergence_factor;
    if (zoom_speed < 0) {
        zoom_speed = std::min(zoom_speed, -m_min_zoom_speed);
    } else {
        zoom_speed = std::max(zoom_speed, m_min_zoom_speed);
    }
    float final_delta = zoom_speed * delta_time.asSeconds();
    if (abs(final_delta) > abs(delta_zoom)) {
        final_delta = delta_zoom;
    }
    m_current_zoom += final_delta;
}

sf::Vector2f Camera::get_offset() const {
    return m_offset;
}

float Camera::get_zoom() const {
    return m_current_zoom;
}

void Camera::set_follow_strategy(std::unique_ptr<FollowStrategy> follow_strategy) {
    m_follow_strategy = std::move(follow_strategy);
}

void Camera::set_offset(sf::Vector2f offset) {
    m_offset = offset;
}

void Camera::set_zoom(float zoom) {
    m_current_zoom = zoom;
    m_expected_zoom = zoom;
}

void Camera::zoom_in() {
    m_expected_zoom /= m_zoom_factor;
}

void Camera::zoom_out() {
    m_expected_zoom *= m_zoom_factor;
}
