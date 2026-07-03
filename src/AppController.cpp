#include "AppController.h"
#include "Room.h"

AppController::AppController() {
    db = std::make_unique<DatabaseManager>("relay.db");
}

bool AppController::login(const std::string& username,
                           const std::string& password) {
    if (username.empty() || password.empty()) return false;
    currentUser = db->loginUser(username, password);
    return currentUser != nullptr;
}

bool AppController::registerUser(const std::string& username,
                                  const std::string& password) {
    if (username.empty() || password.empty()) return false;
    return db->registerUser(username, password);
}

void AppController::logout() {
    currentUser = nullptr;
    currentRoom = nullptr;
}

bool AppController::createRoom(const std::string& name) {
    if (!currentUser || name.empty()) return false;
    return db->createRoom(name, currentUser->getID());
}

bool AppController::joinRoom(int roomID) {
    if (!currentUser) return false;
    return db->joinRoom(currentUser->getID(), roomID);
}

void AppController::selectRoom(int roomID) {
    auto rooms = db->getAllRooms();
    for (auto& room : rooms) {
        if (room->getID() == roomID) {
            currentRoom = room;
            return;
        }
    }
}

std::vector<std::shared_ptr<Room>> AppController::getRooms() {
    return db->getAllRooms();
}

bool AppController::sendMessage(const std::string& content) {
    if (!currentUser || !currentRoom || content.empty())
        return false;
    return db->saveMessage(
        currentRoom->getID(),
        currentUser->getID(),
        content,
        currentUser->getUsername()
    );
}

std::vector<std::shared_ptr<Message>>
AppController::getMessages() {
    if (!currentRoom) return {};
    return db->getMessages(currentRoom->getID());
}

bool AppController::clearCurrentChat() {
    if (!currentRoom) return false;
    return db->clearRoomMessages(currentRoom->getID());
}

std::shared_ptr<User> AppController::getCurrentUser() const {
    return currentUser;
}

std::shared_ptr<Room> AppController::getCurrentRoom() const {
    return currentRoom;
}

bool AppController::isLoggedIn() const {
    return currentUser != nullptr;
}