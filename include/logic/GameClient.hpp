#ifndef MADNESS_TACTICAL_GAMECLIENT_HPP
#define MADNESS_TACTICAL_GAMECLIENT_HPP

#include <SFML/System/Clock.hpp>
#include <SFML/System/Sleep.hpp>
#include <SFML/Network/TcpListener.hpp>
#include <SFML/Network/TcpSocket.hpp>
#include <SFML/Network/Packet.hpp>
#include <vector>
#include <memory>
#include <map>
#include <iostream>
#include <thread>
#include <logic/events/EventType.hpp>


class GameClient
{
public:
    explicit GameClient();
//    ~GameServer();

    void start_client();

    void process_event();


//    void sendPlayerEvent(const EventType& event, int player_id);

    void connect_to_server();

private:

    sf::Packet event_to_packet(const EventType& event);
    EventType packet_to_event(sf::Packet);
    std::vector<EventType> events_for_next_tick;

    std::vector<EventType> get_tick_events();

    void send_packet_server(sf::Packet);

    void do_event(EventType event);

     [[noreturn]] void start_listening();

    int                 port;

    std::map<EventType, std::string> EVENT_TO_STRING_MAP;
    std::map<std::string, EventType> STRING_TO_EVENT_MAP;


    sf::TcpSocket client_socket;
void process_event(EventType event);
};

#endif //MADNESS_TACTICAL_GAMECLIENT_HPP
