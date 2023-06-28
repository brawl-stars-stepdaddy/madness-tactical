#include "logic/GameClient.hpp"
#include "logic/events/event_data/AddUnitEventData.hpp"

GameClient::GameClient() {
    m_port = 50000;
    m_event_to_string_map = {
        {EventType::CHANGE_ANGLE_UP, "CHANGE_ANGLE_UP"},
        {EventType::CHANGE_ANGLE_DOWN, "CHANGE_ANGLE_DOWN"},
        {EventType::MOVE_LEFT, "MOVE_LEFT"},
        {EventType::MOVE_RIGHT, "MOVE_RIGHT"},
        {EventType::JUMP_FORWARD, "JUMP_FORWARD"},
        {EventType::JUMP_BACKWARD, "JUMP_BACKWARD"},
        {EventType::BEGIN_CHARGE_WEAPON, "BEGIN_CHARGE_WEAPON"},
        {EventType::LAUNCH_PROJECTILE, "LAUNCH_PROJECTILE"},
        {EventType::ZOOM_IN, "ZOOM_IN"},
        {EventType::ZOOM_OUT, "ZOOM_OUT"},
        {EventType::CAMERA_MOVE_LEFT, "CAMERA_MOVE_LEFT"},
        {EventType::CAMERA_MOVE_RIGHT, "CAMERA_MOVE_RIGHT"},
        {EventType::CAMERA_MOVE_UP, "CAMERA_MOVE_UP"},
        {EventType::CAMERA_MOVE_DOWN, "CAMERA_MOVE_DOWN"},
        {EventType::ADD_UNIT, "ADD_UNIT"},
    };

    m_string_to_event_map = {
        {"CHANGE_ANGLE_UP", EventType::CHANGE_ANGLE_UP},
        {"CHANGE_ANGLE_DOWN", EventType::CHANGE_ANGLE_DOWN},
        {"MOVE_LEFT", EventType::MOVE_LEFT},
        {"MOVE_RIGHT", EventType::MOVE_RIGHT},
        {"JUMP_FORWARD", EventType::JUMP_FORWARD},
        {"JUMP_BACKWARD", EventType::JUMP_BACKWARD},
        {"BEGIN_CHARGE_WEAPON", EventType::BEGIN_CHARGE_WEAPON},
        {"LAUNCH_PROJECTILE", EventType::LAUNCH_PROJECTILE},
        {"ZOOM_IN", EventType::ZOOM_IN},
        {"ZOOM_OUT", EventType::ZOOM_OUT},
        {"CAMERA_MOVE_LEFT", EventType::CAMERA_MOVE_LEFT},
        {"CAMERA_MOVE_RIGHT", EventType::CAMERA_MOVE_RIGHT},
        {"CAMERA_MOVE_UP", EventType::CAMERA_MOVE_UP},
        {"CAMERA_MOVE_DOWN", EventType::CAMERA_MOVE_DOWN},
        {"ADD_UNIT", EventType::ADD_UNIT},
    };
}

void GameClient::start_client() {
    start_listening();
}

void GameClient::start_listening() {
    m_thread = std::thread([this](){
        m_is_running = true;
        connect_to_server();
        while (m_is_running) {
             sf::Packet packet;
             m_client_socket.receive(packet);
             if (packet.getDataSize() != 0) {
                 std::string packet_type;
                 if (packet_type == "start_game") {
                     packet >> m_number;
                     m_is_ready = true;
                 }
                 if (packet_type == "end_game") {
                     m_is_ready = true;
                     return;
                 }
                 if (packet_type == "end_turn") {
                     m_is_ready = true;
                 }
                 if (packet_type == "event") {
                     m_events_for_next_tick.push_back(packet_to_event(packet));
                 }
            }
        }
    });
}

std::vector<EventType> GameClient::get_tick_events() {
    m_is_ready = false;
    auto save_events_for_next_tick = m_events_for_next_tick;
    m_events_for_next_tick.clear();
    return save_events_for_next_tick;
}

void GameClient::connect_to_server() {
    sf::IpAddress server_ip("localhost");
    m_client_socket.connect(server_ip, m_port);
}

void GameClient::send_packet_server(sf::Packet packet) {
    m_client_socket.send(packet);
}

EventType GameClient::packet_to_event(sf::Packet packet) {
    std::string event_string;
    packet >> event_string;
    return m_string_to_event_map[event_string];
}

sf::Packet GameClient::event_to_packet(const EventType& event) {
    sf::Packet packet;
    packet << m_event_to_string_map[event];
    return packet;
}

void GameClient::process_event(EventType event) {
    send_packet_server(event_to_packet(event));
}

bool GameClient::is_ready() {
    return m_is_ready;
}

bool GameClient::is_running() {
    return m_is_running;
}

void GameClient::close() {
    m_is_running = false;
    m_thread.join();
}

int GameClient::get_number() {
    return m_number;
}
