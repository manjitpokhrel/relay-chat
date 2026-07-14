#include "RemoteDataService.h"
#include <iostream>

static std::string extractJSON(
    const std::string& json,
    const std::string& key) {
    std::string searchStr = "\"" + key + "\":";
    size_t pos = json.find(searchStr);
    if (pos == std::string::npos) return "";
    pos += searchStr.size();
    if (json[pos] == '"') {
        pos++;
        size_t end = json.find('"', pos);
        return json.substr(pos, end - pos);
    } else {
        size_t end = json.find_first_of(",}", pos);
        return json.substr(pos, end - pos);
    }
}

RemoteDataService::RemoteDataService(
    const std::string& serverUrl)
    : network(
        std::make_unique<ClientNetworkManager>(
            serverUrl)),
      serverUrl(serverUrl) {}

bool RemoteDataService::registerUser(
    const std::string& username,
    const std::string& password) {
    httplib::Params params;
    params.emplace("username", username);
    params.emplace("password", password);
    std::string res =
        network->post("/register", params);
    return res.find("true") != std::string::npos;
}

std::shared_ptr<User>
RemoteDataService::loginUser(
    const std::string& username,
    const std::string& password) {
    httplib::Params params;
    params.emplace("username", username);
    params.emplace("password", password);
    std::string res =
        network->post("/login", params);
    if (res.find("true") == std::string::npos)
        return nullptr;
    std::string idStr =
        extractJSON(res, "userID");
    std::string uname =
        extractJSON(res, "username");
    if (idStr.empty()) return nullptr;
    return std::make_shared<User>(
        std::stoi(idStr), uname, "");
}

bool RemoteDataService::createRoom(
    const std::string& name,
    int userID) {
    httplib::Params params;
    params.emplace("name", name);
    params.emplace("userID",
        std::to_string(userID));
    std::string res =
        network->post("/rooms", params);
    return res.find("true") != std::string::npos;
}

std::vector<std::shared_ptr<Room>>
RemoteDataService::getAllRooms() {
    std::vector<std::shared_ptr<Room>> rooms;
    std::string res = network->get("/rooms");
    size_t pos = 0;
    while ((pos = res.find("{", pos)) !=
           std::string::npos) {
        size_t end = res.find("}", pos);
        std::string obj =
            res.substr(pos, end - pos + 1);
        std::string idStr =
            extractJSON(obj, "id");
        std::string name =
            extractJSON(obj, "name");
        std::string cbStr =
            extractJSON(obj, "createdBy");
        if (!idStr.empty() && !name.empty()) {
            rooms.push_back(
                std::make_shared<Room>(
                    std::stoi(idStr), name,
                    cbStr.empty() ? 0 :
                    std::stoi(cbStr)));
        }
        pos = end + 1;
    }
    return rooms;
}

bool RemoteDataService::joinRoom(
    int userID, int roomID) {
    httplib::Params params;
    params.emplace("userID",
        std::to_string(userID));
    std::string path = "/rooms/" +
        std::to_string(roomID) + "/join";
    std::string res =
        network->post(path, params);
    return res.find("true") != std::string::npos;
}

bool RemoteDataService::saveMessage(
    int roomID, int userID,
    const std::string& content,
    const std::string& senderName) {
    httplib::Params params;
    params.emplace("userID",
        std::to_string(userID));
    params.emplace("senderName", senderName);
    params.emplace("content", content);
    std::string path = "/rooms/" +
        std::to_string(roomID) + "/messages";
    std::string res =
        network->post(path, params);
    return res.find("true") != std::string::npos;
}

std::vector<std::shared_ptr<Message>>
RemoteDataService::getMessages(int roomID) {
    std::vector<std::shared_ptr<Message>> messages;
    std::string path = "/rooms/" +
        std::to_string(roomID) + "/messages";
    std::string res = network->get(path);
    size_t pos = 0;
    while ((pos = res.find("{", pos)) !=
           std::string::npos) {
        size_t end = res.find("}", pos);
        std::string obj =
            res.substr(pos, end - pos + 1);
        std::string idStr =
            extractJSON(obj, "id");
        std::string rIDStr =
            extractJSON(obj, "roomID");
        std::string uIDStr =
            extractJSON(obj, "userID");
        std::string sender =
            extractJSON(obj, "senderName");
        std::string content =
            extractJSON(obj, "content");
        std::string ts =
            extractJSON(obj, "timestamp");
        if (!idStr.empty() && !content.empty()) {
            messages.push_back(
                std::make_shared<Message>(
                    std::stoi(idStr),
                    std::stoi(rIDStr),
                    std::stoi(uIDStr),
                    sender, content, ts));
        }
        pos = end + 1;
    }
    return messages;
}

bool RemoteDataService::clearRoomMessages(
    int roomID) {
    std::string path = "/rooms/" +
        std::to_string(roomID) + "/messages";
    std::string res = network->del(path);
    return res.find("true") != std::string::npos;
}