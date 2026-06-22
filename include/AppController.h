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
// Sits between GUI and data layer.
// GUI never calls database directly.
// Everything flows through here.
class AppController {
private:
    std::unique_ptr<IDataService> service;
    std::shared_ptr<User> currentUser;
    std::shared_ptr<Room> currentRoom;

public:
    explicit AppController(
        std::unique_ptr<IDataService> service);
};

#endif