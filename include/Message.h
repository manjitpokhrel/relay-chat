#ifndef MESSAGE_H
#define MESSAGE_H

#include "BaseEntity.h"
#include <string>

// Represents a single chat message.
// Inherits from BaseEntity for ID and toString.
class Message : public BaseEntity {
private:
    int roomID;
    int senderID;
    std::string senderName;
    std::string content;
    std::string timestamp;

public:
    Message(int id,
            int roomID,
            int senderID,
            const std::string& senderName,
            const std::string& content,
            const std::string& timestamp)
        : BaseEntity(id),
          roomID(roomID),
          senderID(senderID),
          senderName(senderName),
          content(content),
          timestamp(timestamp) {}

    int getRoomID() const { return roomID; }
    int getSenderID() const { return senderID; }
    std::string getSenderName() const {
        return senderName;
    }
    std::string getContent() const {
        return content;
    }
    std::string getTimestamp() const {
        return timestamp;
    }

    std::string toString() const override {
        return "[" + timestamp + "] "
               + senderName + ": "
               + content;
    }
};

#endif