<<<<<<< HEAD

=======
>>>>>>> c16a75fedbd10fddfd1af035dc0a67bd4ecde023
#ifndef MESSAGE_H
#define MESSAGE_H

#include "BaseEntity.h"
#include <string>

<<<<<<< HEAD
using namespace std;

class Message : public BaseEntity {
    private: 
    int roomID; 
    int senderID;
    string senderName;
    string content;
    string timestamp;

    public:
    Message (int id, int roomID ,senderID, const string& senderName, const string& content, const string& timestamp) 
        : BaseEntity(id), roomID(roomID), senderID(senderID), senderName(senderName), content(content), timestamp(timestamp) {}

        int getRoomID const { return roomID; }
        int getSenderID const { return senderID; }
        string getSenderName const { return senderName; }
        string getContent const { return content; }
        string getTimestamp const { return timestamp; }

        string toString () const override {
            return "[" + timestamp +"] " + senderName + ": " + content; 
        }
};
#endif 

=======
class Message : public BaseEntity {
private:
    int roomID;
    int senderID;
    std::string senderName;
    std::string content;
    std::string timestamp;

public:
    Message(int id, int roomID, int senderID,
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
    std::string getSenderName() const { return senderName; }
    std::string getContent() const { return content; }
    std::string getTimestamp() const { return timestamp; }

    std::string toString() const override {
        return "[" + timestamp + "] " + senderName + ": " + content;
    }
};

#endif
>>>>>>> c16a75fedbd10fddfd1af035dc0a67bd4ecde023
