
#ifndef MESSAGE_H
#define MESSAGE_H

#include "BaseEntity.h"
#include <string>

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

