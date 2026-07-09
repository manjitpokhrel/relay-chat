<<<<<<< HEAD
#include "Message.h"


=======
#include "RemoteDataService.h"

RemoteDataService::RemoteDataService(
    const std::string& serverUrl)
    : network(std::make_unique<ClientNetworkManager>(
        serverUrl)),
      serverUrl(serverUrl) {}

// ─── Auth ──────────────────────────────────────────────

bool RemoteDataService::registerUser(
    const std::string& username,
    const std::string& password) {
    (void)username;
    (void)password;
    // TODO: POST /register
    return false;
}

std::shared_ptr<User> RemoteDataService::loginUser(
    const std::string& username,
    const std::string& password) {
    (void)username;
    (void)password;
    // TODO: POST /login
    return nullptr;
}

// ─── Rooms ─────────────────────────────────────────────

bool RemoteDataService::createRoom(
    const std::string& name,
    int userID) {
    (void)name;
    (void)userID;
    // TODO: POST /rooms
    return false;
}

std::vector<std::shared_ptr<Room>>
RemoteDataService::getAllRooms() {
    // TODO: GET /rooms
    return {};
}

bool RemoteDataService::joinRoom(
    int userID,
    int roomID) {
    (void)userID;
    (void)roomID;
    // TODO: POST /rooms/:id/join
    return false;
}

// ─── Messages ──────────────────────────────────────────

bool RemoteDataService::saveMessage(
    int roomID,
    int userID,
    const std::string& content,
    const std::string& senderName) {
    (void)roomID;
    (void)userID;
    (void)content;
    (void)senderName;
    // TODO: POST /rooms/:id/messages
    return false;
}

std::vector<std::shared_ptr<Message>>
RemoteDataService::getMessages(int roomID) {
    (void)roomID;
    // TODO: GET /rooms/:id/messages
    return {};
}

bool RemoteDataService::clearRoomMessages(int roomID) {
    (void)roomID;
    // TODO: DELETE /rooms/:id/messages
    return false;
}
>>>>>>> 70d55099947c2fb834270d18a27649e7a233efd5
