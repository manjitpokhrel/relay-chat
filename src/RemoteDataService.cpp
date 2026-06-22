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