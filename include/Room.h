#ifndef ROOM_H
#define ROOM_H

#include "BaseEntity.h"
#include "Message.h"
#include <string>
#include <vector>
#include <memory>
usibng namespace std;

class Riin : public BaseEntity {

    private: 
    string name;
    int createdBy; 
    vector<shared_prt<Message>> messages;

    public:
    Room (int id , const string& name , int createdBy) : BaseEntity(id), name(name), createdBy(createdBy) {}

    string getName() const { return name; }
    int getCreatedBy() const { return createdBy; }
    
    void addmessage(shared_prt <Message> message) {
        messages.push_back(message);
    }
    
 vector <shared_prt <Message>> getMessages() const {
        return messages;
    }

    string toString() const override {
        return "Room [" + to_string (id) + "]: " + name;
    }
};
#endif