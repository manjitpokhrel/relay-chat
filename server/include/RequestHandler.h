#ifndef REQUESTHANDLER_H
#define REQUESTHANDLER_H

#include "ServerDB.h"
#include "httplib.h"
#include <memory>

class RequestHandler {
private:
    std::shared_ptr<ServerDB> db;

    void sendJSON(
        httplib::Response& res,
        const std::string& json,
        int status = 200);

    void sendError(
        httplib::Response& res,
        const std::string& message,
        int status = 400);

public:
    explicit RequestHandler(
        std::shared_ptr<ServerDB> db);

    void handleRegister(
        const httplib::Request& req,
        httplib::Response& res);

    void handleLogin(
        const httplib::Request& req,
        httplib::Response& res);

    void handleGetRooms(
        const httplib::Request& req,
        httplib::Response& res);

    void handleCreateRoom(
        const httplib::Request& req,
        httplib::Response& res);

    void handleJoinRoom(
        const httplib::Request& req,
        httplib::Response& res);

    void handleGetMessages(
        const httplib::Request& req,
        httplib::Response& res);

    void handleSendMessage(
        const httplib::Request& req,
        httplib::Response& res);

    void handleClearMessages(
        const httplib::Request& req,
        httplib::Response& res);
};

#endif