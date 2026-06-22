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