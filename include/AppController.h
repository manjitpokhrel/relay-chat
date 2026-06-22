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
class AppController {
private:
    std::unique_ptr<IDataService> service;
    std::shared_ptr<User> currentUser;
    std::shared_ptr<Room> currentRoom;

public:
    explicit AppController(
        std::unique_ptr<IDataService> service);

    // Auth
    bool login(
        const std::string& username,
        const std::string& password);

    bool registerUser(
        const std::string& username,
        const std::string& password);

    void logout();
};

#endif