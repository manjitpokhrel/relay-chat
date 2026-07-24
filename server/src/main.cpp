#include "Server.h"
#include "ServerDB.h"
#include <iostream>

int main(int argc, char* argv[]) {
    // Database credentials for PostgreSQL
    std::string host = "127.0.0.1";
    std::string dbName = "relaydb";
    std::string user = "postgres";
    std::string password = "password"; // <-- Replace with your PostgreSQL password
    int dbPort = 5432;
    int serverPort = 8080;

    std::cout << "Initializing PostgreSQL connection..." << std::endl;
    ServerDB db(host, dbName, user, password, dbPort);

    std::cout << "Starting Relay Server on port " << serverPort << "..." << std::endl;
    Server server(host, dbName, user, password, dbPort, serverPort);
    
    // server.start() returns void
    server.start();

    return 0;
}