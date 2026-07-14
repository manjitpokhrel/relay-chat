#ifndef APPCONTROLLER_H
#define APPCONTROLLER_H

<<<<<<< HEAD
#include "DatabaseManager.h"
=======
#include "IDataService.h"
>>>>>>> 70d55099947c2fb834270d18a27649e7a233efd5
#include "User.h"
#include "Room.h"
#include "Message.h"
#include <memory>
#include <vector>
#include <string>

<<<<<<< HEAD
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
=======
// Brain of the application.
// GUI never calls database directly.
// Everything flows through here.
class AppController {
private:
    // Owns the data service.
    // unique_ptr ensures single ownership.
    std::unique_ptr<IDataService> service;

    // Session state.
    // nullptr means nobody is logged in.
    std::shared_ptr<User> currentUser;

    // nullptr means no room selected.
    std::shared_ptr<Room> currentRoom;

public:
    // Dependency injection.
    // Service passed in from outside.
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

>>>>>>> 70d55099947c2fb834270d18a27649e7a233efd5
    bool createRoom(const std::string& name);
    bool joinRoom(int roomID);
    void selectRoom(int roomID);
    std::vector<std::shared_ptr<Room>> getRooms();

<<<<<<< HEAD
    // Messages
=======
    // ─── Messages ──────────────────────────────────────

>>>>>>> 70d55099947c2fb834270d18a27649e7a233efd5
    bool sendMessage(const std::string& content);
    std::vector<std::shared_ptr<Message>> getMessages();
    bool clearCurrentChat();

<<<<<<< HEAD
    // Getters
=======
    // ─── State Getters ─────────────────────────────────

>>>>>>> 70d55099947c2fb834270d18a27649e7a233efd5
    std::shared_ptr<User> getCurrentUser() const;
    std::shared_ptr<Room> getCurrentRoom() const;
    bool isLoggedIn() const;
};

#endif