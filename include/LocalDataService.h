#ifndef LOCALDATASERVICE_H
#define LOCALDATASERVICE_H

#include "IDataService.h"
#include "DatabaseManager.h"
#include <memory>

// SQLite implementation of IDataService.
class LocalDataService : public IDataService {
private:
    std::unique_ptr<DatabaseManager> db;

public:
    // Opens SQLite database at given path.
    explicit LocalDataService(const QString& dbPath);

    bool registerUser(
        const std::string& username,
        const std::string& password) override;

    std::shared_ptr<User> loginUser(
        const std::string& username,
        const std::string& password) override;

    bool createRoom(
        const std::string& name,
        int userID) override;

    std::vector<std::shared_ptr<Room>>
        getAllRooms() override;

    bool joinRoom(
        int userID,
        int roomID) override;

    bool saveMessage(
        int roomID,
        int userID,
        const std::string& content,
        const std::string& senderName) override;

    std::vector<std::shared_ptr<Message>>
        getMessages(int roomID) override;

    bool clearRoomMessages(int roomID) override;
};

#endif