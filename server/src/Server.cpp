#include "Server.h"
#include <iostream>

Server::Server(
    const std::string& dbHost,
    const std::string& dbName,
    const std::string& dbUser,
    const std::string& dbPass,
    int dbPort,
    int serverPort)
    : port(serverPort) {

    db = std::make_shared<ServerDB>(
        dbHost, dbName, dbUser, dbPass, dbPort);

    if (!db->isConnected()) {
        std::cerr << "Failed to connect to DB.\n";
        return;
    }

    handler = std::make_shared<RequestHandler>(db);
    setupRoutes();
}

void Server::setupRoutes() {
    svr.Post("/register",
        [this](const httplib::Request& req,
               httplib::Response& res) {
        handler->handleRegister(req, res);
    });

    svr.Post("/login",
        [this](const httplib::Request& req,
               httplib::Response& res) {
        handler->handleLogin(req, res);
    });

    svr.Get("/rooms",
        [this](const httplib::Request& req,
               httplib::Response& res) {
        handler->handleGetRooms(req, res);
    });

    svr.Post("/rooms",
        [this](const httplib::Request& req,
               httplib::Response& res) {
        handler->handleCreateRoom(req, res);
    });

    svr.Post(R"(/rooms/(\d+)/join)",
        [this](const httplib::Request& req,
               httplib::Response& res) {
        handler->handleJoinRoom(req, res);
    });

    svr.Get(R"(/rooms/(\d+)/messages)",
        [this](const httplib::Request& req,
               httplib::Response& res) {
        handler->handleGetMessages(req, res);
    });

    svr.Post(R"(/rooms/(\d+)/messages)",
        [this](const httplib::Request& req,
               httplib::Response& res) {
        handler->handleSendMessage(req, res);
    });

    svr.Delete(R"(/rooms/(\d+)/messages)",
        [this](const httplib::Request& req,
               httplib::Response& res) {
        handler->handleClearMessages(req, res);
    });

    std::cout << "Routes configured.\n";
}

void Server::start() {
    std::cout << "Server running on port "
              << port << "\n";
    svr.listen("0.0.0.0", port);
}

void Server::stop() {
    svr.stop();
}