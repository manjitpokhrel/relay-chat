#ifndef SERVER_H
#define SERVER_H

#include "httplib.h"
#include "RequestHandler.h"
#include "ServerDB.h"
#include <memory>
#include <string>

class Server {
private:
    httplib::Server svr;
    std::shared_ptr<ServerDB> db;
    std::shared_ptr<RequestHandler> handler;
    int port;
    void setupRoutes();

public:
    Server(
        const std::string& dbHost,
        const std::string& dbName,
        const std::string& dbUser,
        const std::string& dbPass,
        int dbPort = 5432,
        int serverPort = 8080);

    void start();
    void stop();
};

#endif