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
#include <atomic>


struct GameClient {
public:
    explicit GameClient();

    void start_client();

    std::vector<EventType> get_tick_events();

    bool is_ready();

    bool is_running();

    void close();

    int get_number();

private:
    void connect_to_server();
    void send_packet_server(sf::Packet);
    void process_event(EventType event);
    void start_listening();
    sf::Packet event_to_packet(const EventType& event);
    EventType packet_to_event(sf::Packet);

    std::vector<EventType> m_events_for_next_tick;
    std::map<EventType, std::string> m_event_to_string_map;
    std::map<std::string, EventType> m_string_to_event_map;
    sf::TcpSocket m_client_socket;
    int m_port;
    int m_number;
    std::atomic<bool> m_is_ready = false;
    std::atomic<bool> m_is_running = false;
    std::thread m_thread;
};

#endif //MADNESS_TACTICAL_GAMECLIENT_HPP
