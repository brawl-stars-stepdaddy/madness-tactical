#ifndef MADNESS_TACTICAL_GAMESERVER_HPP
#define MADNESS_TACTICAL_GAMESERVER_HPP

//#include <SFML/System/Thread.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/System/Sleep.hpp>
//#include <SFML/Graphics/Rect.hpp>
#include <SFML/Network/TcpListener.hpp>
#include <SFML/Network/TcpSocket.hpp>
//#include "EventData.hpp"
#include <SFML/Network/SocketSelector.hpp>
#include <SFML/Network/Packet.hpp>

#include <vector>
#include <memory>
#include <map>
#include <iostream>
#include <list>

class GameServer
{
public:
    explicit GameServer(int players_count);
//    ~GameServer();

    void run_server_loop();

private:

    void								handleIncomingConnections();

    void								handleIncomingPackets(int active_player);
    void								handleIncomingEventPacket(sf::Packet packet);
    void								broadcastMessage(sf::Packet packet);

    void                                start_game();

    int                                 port;
    int                                 number_of_players;

    sf::TcpListener                     listener;
    std::vector<sf::TcpSocket*>         players_sockets;
    sf::SocketSelector                  socket_selector;

    bool                                game_ends{};
};

#endif //MADNESS_TACTICAL_GAMECLIENT_HPP