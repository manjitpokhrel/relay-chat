#ifndef IDATASERVICE_H
#define IDATASERVICE_H

#include "User.h"
#include "Room.h"
#include "Message.h"
#include <memory>
#include <vector>
#include <string>

// Abstract interface for data operations.
// Controller talks to this only — not SQLite, not AWS.
// Swap LocalDataService for RemoteDataService in main.cpp

class IDataService {
public:
    virtual ~IDataService() = default;

    // Returns false if username taken.
    virtual bool registerUser(
        const std::string& username,
        const std::string& password) = 0;

     // Returns nullptr if credentials are wrong.
    virtual std::shared_ptr<User> loginUser(
        const std::string& username,
        const std::string& password) = 0;

    // Creates room and auto-joins the creator.
    virtual bool createRoom(
        const std::string& name,
        int userID) = 0;

     // Every user sees every room.
    virtual std::vector<std::shared_ptr<Room>>
        getAllRooms() = 0;

    // Safe to call multiple times
    virtual bool joinRoom(
        int userID,
        int roomID) = 0;

    // senderName stored directly to avoid JOIN queries.
    virtual bool saveMessage(
        int roomID,
        int userID,
        const std::string& content,
        const std::string& senderName) = 0;

     // Called every 2 seconds by QTimer.
    virtual std::vector<std::shared_ptr<Message>>
        getMessages(int roomID) = 0;

    // Triggered by Clear Chat button.
    virtual bool clearRoomMessages(int roomID) = 0;
};

#endif