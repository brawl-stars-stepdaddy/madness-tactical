#include "logic/GameServer.hpp"
#include <iostream>

GameServer::GameServer(int players_count) {
    m_number_of_players = players_count;
    m_port = 50000;
}

void GameServer::run_server_loop() {
    m_listener.listen(m_port);
    m_socket_selector.add(m_listener);

    handleIncomingConnections();
    std::cout << "AllPlayersConnected";

    while (!m_game_ends) {
        handleIncomingPackets();
    }
}

void GameServer::handleIncomingConnections() {
    std::cout << "hui1" << std::endl;
    while (m_players_sockets.size() < m_number_of_players) {
        std::cout << m_players_sockets.size() << ' ' << m_number_of_players << std::endl;
        std::cout << "hui2" << std::endl;
        if (m_socket_selector.wait()) {
            std::cout << "hui3" << std::endl;
            if (m_socket_selector.isReady(m_listener)) {
                std::cout << "hui4" << std::endl;
                auto *client = new sf::TcpSocket;
                m_listener.accept(*client);
                m_players_sockets.push_back(client);
                m_socket_selector.add(*client);
            }
        }
    }
    start_game();
}

void GameServer::start_game() {
    int client_number = 0;
    for (auto client_pointer : m_players_sockets) {
        sf::TcpSocket &client = *client_pointer;
        sf::Packet packet;
        packet << "start game" << client_number;
        client.send(packet);
        client_number++;
    }
}

void GameServer::handleIncomingPackets() {
    while (true) {
        for (int active_player = 0; active_player < m_number_of_players; active_player++) {
            sf::TcpSocket &active_player_socket = *m_players_sockets[active_player];
            sf::Packet packet;
            active_player_socket.receive(packet);
            if (packet.getDataSize() != 0) {
                std::string packet_type;
                packet >> packet_type;
                if (packet_type == "end_of_turn") {
                    sf::Packet p;
                    p << packet_type;
                    handleIncomingEventPacket(p);
                    return;
                }
                if (packet_type == "end_of_game") {
                    m_game_ends = true;
                    return;
                }
                if (packet_type == "event") {
                    handleIncomingEventPacket(packet);
                }
            }
        }
    }
}

void GameServer::broadcastMessage(sf::Packet packet) {
    for (auto client_pointer : m_players_sockets) {
        sf::TcpSocket &client = *client_pointer;
        client.send(packet);
    }
}

void GameServer::handleIncomingEventPacket(sf::Packet packet) {
    broadcastMessage(packet);
}
