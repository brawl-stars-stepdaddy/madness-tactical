#ifndef MADNESS_TACTICAL_GAMECLIENT_HPP
#define MADNESS_TACTICAL_GAMECLIENT_HPP

//#include <SFML/System/Thread.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/System/Sleep.hpp>
//#include <SFML/Graphics/Rect.hpp>
#include <SFML/Network/TcpListener.hpp>
#include <SFML/Network/TcpSocket.hpp>
//#include "EventData.hpp"
#include <SFML/Network/Packet.hpp>

#include <vector>
#include <memory>
#include <map>
#include <iostream>
#include <thread>


class GameClient
{
public:
    explicit GameClient();
//    ~GameServer();

    void start_client();

    void process_event();


//    void sendPlayerEvent(const EventData& event, int player_id);

    [[noreturn]] void connect_to_server();

private:

    sf::Packet event_to_packet();
    void packet_to_event();

    void send_packet_server(sf::Packetpacket);

    void do_event();

     [[noreturn]] void start_listening();

    int         port;
    sf::TcpSocket client_socket;
};

#endif //MADNESS_TACTICAL_GAMECLIENT_HPP
