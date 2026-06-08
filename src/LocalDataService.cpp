#include "LocalDataService.h"

// Opens DB connection by passing path to DatabaseManager.
// DatabaseManager handles the actual SQLite setup.
LocalDataService::LocalDataService(const QString& dbPath)
    : db(std::make_unique<DatabaseManager>(dbPath)) {}

bool LocalDataService::registerUser(
    const std::string& username,
    const std::string& password) {
    return db->registerUser(username, password);
}

std::shared_ptr<User> LocalDataService::loginUser(
    const std::string& username,
    const std::string& password) {
    return db->loginUser(username, password);
}

bool LocalDataService::createRoom(
    const std::string& name,
    int userID) {
    return db->createRoom(name, userID);
}

std::vector<std::shared_ptr<Room>>
LocalDataService::getAllRooms() {
    return db->getAllRooms();
}

bool LocalDataService::joinRoom(
    int userID,
    int roomID) {
    return db->joinRoom(userID, roomID);
}

bool LocalDataService::saveMessage(
    int roomID,
    int userID,
    const std::string& content,
    const std::string& senderName) {
    return db->saveMessage(
        roomID, userID, content, senderName
    );
}

std::vector<std::shared_ptr<Message>>
LocalDataService::getMessages(int roomID) {
    return db->getMessages(roomID);
}

bool LocalDataService::clearRoomMessages(int roomID) {
    return db->clearRoomMessages(roomID);
}