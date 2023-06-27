#include "logic/GameClient.hpp"

GameClient::EVENT_TO_STRING_MAP = {{EventType::CHANGE_ANGLE_UP, "CHANGE_ANGLE_UP"},
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
              {EventType::CAMERA_MOVE_DOWN, "CAMERA_MOVE_DOWN"}};

GameClient::STRING_TO_EVENT_MAP = {{"CHANGE_ANGLE_UP", EventType::CHANGE_ANGLE_UP},
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
              {"CAMERA_MOVE_DOWN", EventType::CAMERA_MOVE_DOWN}};

GameClient::GameClient() {
    port = 50000;
}

void GameClient::start_client() {
    start_listening();
}

void start_game() {
    // в отдельном потоке
    // todo
}

void GameClient::start_listening() {

    std::thread t1([this](){
         while (true) {
            sf::Packet packet;
            client_socket.receive(packet);
            if (packet.getDataSize() != 0) {
                std::string packet_type;
                if (packet_type == "start_game") {
                    start_game();
                }
                if (packet_type == "end_game") {
                    return;
                }
                if (packet_type == "event") {
                    events_for_next_tick.push_back(packet_to_event(packet));
                }
            }
        }
     });
}

std::vector<EventType> GameClient::get_tick_events() {
        auto save_events_for_next_tick = events_for_next_tick;
        events_for_next_tick.clear();
        return save_events_for_next_tick;
    }

void GameClient::connect_to_server() {
    sf::IpAddress server_ip("localhost");
    client_socket.connect(server_ip, port);
}

void GameClient::send_packet_server(sf::Packet packet) {
    client_socket.send(packet);
}

EventType GameClient::packet_to_event(sf::Packet packet) {
    std::string event_string;
    packet >> event_string;
    return STRING_TO_EVENT_MAP[event_string];
}

sf::Packet GameClient::event_to_packet(const EventType& event) {
    sf::Packet packet;
    packet << EVENT_TO_STRING_MAP[event];
    return packet;
}

void GameClient::process_event(EventType event) {
    send_packet_server(event_to_packet(event));
}
