#ifndef MADNESS_TACTICAL_GAMESERVER_HPP
#define MADNESS_TACTICAL_GAMESERVER_HPP

#include <SFML/Network/TcpListener.hpp>
#include <SFML/Network/TcpSocket.hpp>
#include <SFML/Network/SocketSelector.hpp>
#include <SFML/Network/Packet.hpp>

#include <vector>
#include <memory>
#include <map>
#include <iostream>
#include <list>

struct GameServer {
public:
    explicit GameServer(int players_count);

    void run_server_loop();

private:
    void handleIncomingConnections();
    void handleIncomingPackets();
    void handleIncomingEventPacket(sf::Packet packet);
    void broadcastMessage(sf::Packet packet);
    void start_game();

    int m_port;
    int m_number_of_players;
    sf::TcpListener m_listener;
    std::vector<sf::TcpSocket*> m_players_sockets;
    sf::SocketSelector m_socket_selector;
    bool m_game_ends{};
};

#endif //MADNESS_TACTICAL_GAMECLIENT_HPP