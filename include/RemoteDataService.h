#ifndef REMOTEDATASERVICE_H
#define REMOTEDATASERVICE_H

#include "IDataService.h"
#include "ClientNetworkManager.h"
#include <memory>
#include <string>

// Future AWS implementation of IDataService.
// Replaces LocalDataService when moving to multi-device.
// Controller code stays completely identical.
// Only main.cpp changes — one line swap.
class RemoteDataService : public IDataService {
private:
    std::unique_ptr<ClientNetworkManager> network;
    std::string serverUrl;

public:
    explicit RemoteDataService(
        const std::string& serverUrl);

    // Auth
    bool registerUser(
        const std::string& username,
        const std::string& password) override;

    std::shared_ptr<User> loginUser(
        const std::string& username,
        const std::string& password) override;

    // Rooms
    bool createRoom(
        const std::string& name,
        int userID) override;

    std::vector<std::shared_ptr<Room>>
    getAllRooms() override;

    bool joinRoom(
        int userID,
        int roomID) override;

    // Messages
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