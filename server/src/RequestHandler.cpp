#include "RequestHandler.h"
#include <iostream>

RequestHandler::RequestHandler(
    std::shared_ptr<ServerDB> db)
    : db(db) {}

void RequestHandler::sendJSON(
    httplib::Response& res,
    const std::string& json,
    int status) {
    res.status = status;
    res.set_content(json, "application/json");
}

void RequestHandler::sendError(
    httplib::Response& res,
    const std::string& message,
    int status) {
    res.status = status;
    res.set_content(
        "{\"error\":\"" + message + "\"}",
        "application/json");
}

void RequestHandler::handleRegister(
    const httplib::Request& req,
    httplib::Response& res) {
    auto username = req.get_param_value("username");
    auto password = req.get_param_value("password");
    if (username.empty() || password.empty()) {
        sendError(res,
            "Username and password required");
        return;
    }
    if (db->registerUser(username, password)) {
        sendJSON(res, "{\"success\":true}");
    } else {
        sendError(res,
            "Username already taken", 409);
    }
}

void RequestHandler::handleLogin(
    const httplib::Request& req,
    httplib::Response& res) {
    auto username = req.get_param_value("username");
    auto password = req.get_param_value("password");
    if (username.empty() || password.empty()) {
        sendError(res,
            "Username and password required");
        return;
    }
    int userID = db->loginUser(username, password);
    if (userID != -1) {
        sendJSON(res,
            "{\"success\":true,"
            "\"userID\":" +
            std::to_string(userID) + ","
            "\"username\":\"" + username + "\"}");
    } else {
        sendError(res,
            "Invalid credentials", 401);
    }
}

void RequestHandler::handleGetRooms(
    const httplib::Request& req,
    httplib::Response& res) {
    (void)req;
    sendJSON(res, db->getAllRoomsJSON());
}

void RequestHandler::handleCreateRoom(
    const httplib::Request& req,
    httplib::Response& res) {
    auto name = req.get_param_value("name");
    auto userIDStr = req.get_param_value("userID");
    if (name.empty() || userIDStr.empty()) {
        sendError(res,
            "Name and userID required");
        return;
    }
    int userID = std::stoi(userIDStr);
    int roomID = db->createRoom(name, userID);
    if (roomID != -1) {
        sendJSON(res,
            "{\"success\":true,"
            "\"roomID\":" +
            std::to_string(roomID) + "}");
    } else {
        sendError(res,
            "Room name already taken", 409);
    }
}

void RequestHandler::handleJoinRoom(
    const httplib::Request& req,
    httplib::Response& res) {
    auto userIDStr = req.get_param_value("userID");
    auto roomIDStr = req.matches[1];
    if (userIDStr.empty()) {
        sendError(res, "userID required");
        return;
    }
    int userID = std::stoi(userIDStr);
    int roomID = std::stoi(roomIDStr);
    if (db->joinRoom(userID, roomID)) {
        sendJSON(res, "{\"success\":true}");
    } else {
        sendError(res, "Failed to join room");
    }
}

void RequestHandler::handleGetMessages(
    const httplib::Request& req,
    httplib::Response& res) {
    auto roomIDStr = req.matches[1];
    int roomID = std::stoi(roomIDStr);
    sendJSON(res, db->getMessagesJSON(roomID));
}

void RequestHandler::handleSendMessage(
    const httplib::Request& req,
    httplib::Response& res) {
    auto roomIDStr = req.matches[1];
    auto userIDStr = req.get_param_value("userID");
    auto senderName =
        req.get_param_value("senderName");
    auto content = req.get_param_value("content");
    if (content.empty() || userIDStr.empty()) {
        sendError(res,
            "userID and content required");
        return;
    }
    int roomID = std::stoi(roomIDStr);
    int userID = std::stoi(userIDStr);
    if (db->saveMessage(
            roomID, userID,
            senderName, content)) {
        sendJSON(res, "{\"success\":true}");
    } else {
        sendError(res,
            "Failed to save message");
    }
}

void RequestHandler::handleClearMessages(
    const httplib::Request& req,
    httplib::Response& res) {
    auto roomIDStr = req.matches[1];
    int roomID = std::stoi(roomIDStr);
    if (db->clearMessages(roomID)) {
        sendJSON(res, "{\"success\":true}");
    } else {
        sendError(res,
            "Failed to clear messages");
    }
}