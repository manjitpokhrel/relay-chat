#ifndef DATABASEMANAGER_H
#define DATABASEMANAGER_H

#include "User.h"
#include "Room.h"
#include "Message.h"
#include <QString>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>
#include <memory>
#include <vector>

class DatabaseManager {
private:
    QSqlDatabase db;

    void initializeTables();

public:
    DatabaseManager(const QString& dbPath);
    ~DatabaseManager();

    // User operations
    bool registerUser(const std::string& username,
                      const std::string& password);
    std::shared_ptr<User> loginUser(const std::string& username,
                                     const std::string& password);

    // Room operations
    bool createRoom(const std::string& name, int userID);
    std::vector<std::shared_ptr<Room>> getAllRooms();
    bool joinRoom(int userID, int roomID);

    // Message operations
    bool saveMessage(int roomID, int userID,
                     const std::string& content,
                     const std::string& senderName);
    std::vector<std::shared_ptr<Message>> getMessages(int roomID);
    bool clearRoomMessages(int roomID);
};

#endif