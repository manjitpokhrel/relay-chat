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

// ─── Rooms ─────────────────────────────────────────────

bool AppController::createRoom(const std::string& name) {
    if (!currentUser || name.empty())
        return false;
    return service->createRoom(
        name, currentUser->getID());
}

bool AppController::joinRoom(int roomID) {
    if (!currentUser) return false;
    return service->joinRoom(
        currentUser->getID(), roomID);
}

void AppController::selectRoom(int roomID) {
    auto rooms = service->getAllRooms();
    for (auto& room : rooms) {
        if (room->getID() == roomID) {
            currentRoom = room;
            return;
        }
    }
    currentRoom = nullptr;
}

std::vector<std::shared_ptr<Room>>
AppController::getRooms() {
    return service->getAllRooms();
}