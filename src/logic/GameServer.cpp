#include "logic/GameServer.hpp"

GameServer::GameServer(int players_count) {
    number_of_players = players_count;
    port = 50000;
}

void GameServer::run_server_loop() {
    listener.listen(port);
    socket_selector.add(listener);

    sf::Time stepInterval = sf::seconds(1.f / 60.f);
    sf::Time stepTime = sf::Time::Zero;
    sf::Time tickInterval = sf::seconds(1.f / 20.f);
    sf::Time tickTime = sf::Time::Zero;
    sf::Clock stepClock, tickClock;

    handleIncomingConnections();
    std::cout << "AllPlayersConnected";

    int active_player = 0;
    while (!game_ends) {
        handleIncomingPackets(active_player);
        active_player += 1;
        active_player %= players_sockets.size();
    }

}

void GameServer::handleIncomingConnections() {

    while (players_sockets.size() < number_of_players)
    {
        if (socket_selector.wait())
        {
            if (socket_selector.isReady(listener))
            {
                auto *client = new sf::TcpSocket;
                if (listener.accept(*client) == sf::Socket::Done)
                {
                    // Add the new client to the players_sockets list
                    players_sockets.push_back(client);
                    // Add the new client to the socket_selector so that we will
                    // be notified when he sends something
                    socket_selector.add(*client);
                }
                else
                {
                    // Error, we won't get a new connection, delete the socket
                    delete client;
                }
            }
        }
    }
    start_game();
}

void GameServer::start_game() {
    sf::Packet start_game_packet;
    start_game_packet << "start_game";
    broadcastMessage(start_game_packet);
}

void GameServer::handleIncomingPackets(int active_player) {
    while (true)
    {
        sf::TcpSocket &active_player_socket = *players_sockets[active_player];
        sf::Packet packet;
        active_player_socket.receive(packet);
        if (packet.getDataSize() != 0) {

            std::string packet_type;
            packet >> packet_type;
            if (packet_type == "end_of_turn") {
                return;
            }

            if (packet_type == "end_of_game") {
                game_ends = true;
                return;
            }

            if (packet_type == "event") {
                handleIncomingEventPacket(packet);
            }
        }
    }
}

void GameServer::broadcastMessage(sf::Packet packet) {
    for (auto client_pointer: players_sockets) {
        sf::TcpSocket &client = *client_pointer;
        client.send(packet);
    }
}

void GameServer::handleIncomingEventPacket(sf::Packet packet) {
    broadcastMessage(packet);
}
