#ifndef APPCONTROLLER_H
#define APPCONTROLLER_H

#include "DatabaseManager.h"
#include "User.h"
#include "Room.h"
#include "Message.h"
#include <memory>
#include <vector>
#include <string>

class AppController {
private:
    std::unique_ptr<DatabaseManager> db;
    std::shared_ptr<User> currentUser;
    std::shared_ptr<Room> currentRoom;

public:
    AppController();

    // Auth
    bool login(const std::string& username,
               const std::string& password);
    bool registerUser(const std::string& username,
                      const std::string& password);
    void logout();

    // Rooms
    bool createRoom(const std::string& name);
    bool joinRoom(int roomID);
    void selectRoom(int roomID);
    std::vector<std::shared_ptr<Room>> getRooms();

    // Messages
    bool sendMessage(const std::string& content);
    std::vector<std::shared_ptr<Message>> getMessages();
    bool clearCurrentChat();

    // Getters
    std::shared_ptr<User> getCurrentUser() const;
    std::shared_ptr<Room> getCurrentRoom() const;
    bool isLoggedIn() const;
};

#endif