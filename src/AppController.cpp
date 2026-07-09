#include "AppController.h"
<<<<<<< HEAD
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
=======

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
>>>>>>> 70d55099947c2fb834270d18a27649e7a233efd5
}

void AppController::logout() {
    currentUser = nullptr;
    currentRoom = nullptr;
}

<<<<<<< HEAD
bool AppController::createRoom(const std::string& name) {
    if (!currentUser || name.empty()) return false;
    return db->createRoom(name, currentUser->getID());
=======
// ─── Rooms ─────────────────────────────────────────────

bool AppController::createRoom(const std::string& name) {
    if (!currentUser || name.empty())
        return false;
    return service->createRoom(
        name, currentUser->getID());
>>>>>>> 70d55099947c2fb834270d18a27649e7a233efd5
}

bool AppController::joinRoom(int roomID) {
    if (!currentUser) return false;
<<<<<<< HEAD
    return db->joinRoom(currentUser->getID(), roomID);
}

void AppController::selectRoom(int roomID) {
    auto rooms = db->getAllRooms();
=======
    return service->joinRoom(
        currentUser->getID(), roomID);
}

void AppController::selectRoom(int roomID) {
    auto rooms = service->getAllRooms();
>>>>>>> 70d55099947c2fb834270d18a27649e7a233efd5
    for (auto& room : rooms) {
        if (room->getID() == roomID) {
            currentRoom = room;
            return;
        }
    }
<<<<<<< HEAD
}

std::vector<std::shared_ptr<Room>> AppController::getRooms() {
    return db->getAllRooms();
}

bool AppController::sendMessage(const std::string& content) {
    if (!currentUser || !currentRoom || content.empty())
        return false;
    return db->saveMessage(
=======
    currentRoom = nullptr;
}

std::vector<std::shared_ptr<Room>>
AppController::getRooms() {
    return service->getAllRooms();
}

// ─── Messages ──────────────────────────────────────────

bool AppController::sendMessage(
    const std::string& content) {
    if (!currentUser || !currentRoom || content.empty())
        return false;
    return service->saveMessage(
>>>>>>> 70d55099947c2fb834270d18a27649e7a233efd5
        currentRoom->getID(),
        currentUser->getID(),
        content,
        currentUser->getUsername()
    );
}

std::vector<std::shared_ptr<Message>>
AppController::getMessages() {
    if (!currentRoom) return {};
<<<<<<< HEAD
    return db->getMessages(currentRoom->getID());
=======
    return service->getMessages(currentRoom->getID());
>>>>>>> 70d55099947c2fb834270d18a27649e7a233efd5
}

bool AppController::clearCurrentChat() {
    if (!currentRoom) return false;
<<<<<<< HEAD
    return db->clearRoomMessages(currentRoom->getID());
}

std::shared_ptr<User> AppController::getCurrentUser() const {
    return currentUser;
}

std::shared_ptr<Room> AppController::getCurrentRoom() const {
=======
    return service->clearRoomMessages(
        currentRoom->getID());
}

// ─── State ─────────────────────────────────────────────

std::shared_ptr<User>
AppController::getCurrentUser() const {
    return currentUser;
}

std::shared_ptr<Room>
AppController::getCurrentRoom() const {
>>>>>>> 70d55099947c2fb834270d18a27649e7a233efd5
    return currentRoom;
}

bool AppController::isLoggedIn() const {
    return currentUser != nullptr;
}