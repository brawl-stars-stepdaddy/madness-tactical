#include "logic/Application.hpp"
#include "logic/GameClient.hpp"
#include "logic/GameServer.hpp"


//int main() {
//    GameServer server(2);
//    server.run_server_loop();
//
//    GameClient player1;
//    player1.start_client();
//}


int main() {
    Application application;
    application.run();
    return 0;
}


