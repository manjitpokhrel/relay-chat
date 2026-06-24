#include "AppController.h"

AppController::AppController(
    std::unique_ptr<IDataService> service)
    : service(std::move(service)) {}

// ─── Auth ──────────────────────────────────────────────

bool AppController::login(
    const std::string& username,
    const std::string& password) {
    if (username.empty() || password.empty())
        return false;
    currentUser = service->loginUser(username, password);
    return currentUser != nullptr;
}

bool AppController::registerUser(
    const std::string& username,
    const std::string& password) {
    if (username.empty() || password.empty())
        return false;
    return service->registerUser(username, password);
}

void AppController::logout() {
    currentUser = nullptr;
    currentRoom = nullptr;
}