#include "Server.h"
#include "ServerDB.h"
#include <iostream>

int main(int argc, char* argv[]) {
    std::cout << "Starting Relay Server on port 8080..." << std::endl;

    // Initialize database connection/tables
    ServerDB db("relay_server.db");

    // Initialize and start the network server
    Server server(8080, db);
    if (server.start()) {
        std::cout << "Relay Server running successfully." << std::endl;
    } else {
        std::cerr << "Failed to start Relay Server." << std::endl;
        return 1;
    }

    return 0;
}