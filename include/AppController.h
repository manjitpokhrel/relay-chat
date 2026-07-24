#ifndef APPCONTROLLER_H
#define APPCONTROLLER_H

#include "IDataService.h"
#include "User.h"
#include "Room.h"
#include "Message.h"
#include <memory>
#include <vector>
#include <string>

// Brain of the application.
// GUI never calls database directly.
// Everything flows through here.
class AppController {
private:
    // Owns the data service.
    // unique_ptr ensures single ownership.
    std::unique_ptr<IDataService> service;

    // nullptr means nobody is logged in.
    std::shared_ptr<User> currentUser;

    // nullptr means no room selected.
    std::shared_ptr<Room> currentRoom;

public:
    // Dependency injection.
    // Controller never creates its own DB connection.
    explicit AppController(
        std::unique_ptr<IDataService> service);

    // ─── Auth ──────────────────────────────────────────

    // Returns false if credentials are wrong.
    bool login(
        const std::string& username,
        const std::string& password);

    // Returns false if username already taken.
    bool registerUser(
        const std::string& username,
        const std::string& password);

    // Clears session state.
    void logout();

    // ─── Rooms ─────────────────────────────────────────

    bool createRoom(const std::string& name);
    bool joinRoom(int roomID);
    void selectRoom(int roomID);
    std::vector<std::shared_ptr<Room>> getRooms();

    // ─── Messages ──────────────────────────────────────

    bool sendMessage(const std::string& content);
    std::vector<std::shared_ptr<Message>> getMessages();
    bool clearCurrentChat();

    // ─── State Getters ─────────────────────────────────

    std::shared_ptr<User> getCurrentUser() const;
    std::shared_ptr<Room> getCurrentRoom() const;
    bool isLoggedIn() const;
};

#endif