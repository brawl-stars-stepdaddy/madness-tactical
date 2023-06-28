#include "logic/GameServer.hpp"

int main() {
    GameServer server(2);
    server.run_server_loop();
    return 0;
}