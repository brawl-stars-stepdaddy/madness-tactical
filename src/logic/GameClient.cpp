#include "logic/GameClient.hpp"

GameClient::GameClient() {
}

void GameClient::start_client() {
    start_listening();
}

void start_game() {
    // в отдельном потоке
    // запустить игру к илье;
}

void GameClient::start_listening() {
    std::thread t1([this](){;
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
                    do_event(packet_to_event(packet));
                }
            }
        }
     });
}

void GameClient::connect_to_server() {
    sf::IpAddress server_ip("localhost");
    client_socket.connect(server_ip, port);
}

void GameClient::send_packet_server(sf::Packet packet) {
    client_socket.send(packet);
}

//тут тип эвента а не void
void GameClient::packet_to_event() {
    //todo
}

void GameClient::do_event() {
    //к илье
}

sf::Packet GameClient::event_to_packet() {
    //todo
    return sf::Packet();
}
