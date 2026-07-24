#ifndef ROOM_H
#define ROOM_H

#include "BaseEntity.h"
#include "Message.h"
#include <string>
#include <cstddef>
#include <vector>
#include <memory>
using namespace std;

class Room : public BaseEntity {

    private: 
    string name;
    int createdBy; 
    vector<shared_ptr<Message>> messages;

    public:
    Room (int id , const string& name , int createdBy) : BaseEntity(id), name(name), createdBy(createdBy) {}

    string getName() const { return name; }
    int getCreatedBy() const { return createdBy; }
    
    void addMessage(shared_ptr<Message> message) {
    messages.push_back(message);
}
    
    vector<shared_ptr<Message>> getMessages() const {
        return messages;
    }

    string toString() const override {
        return "Room [" + to_string(id) + "]: " + name;
    }
};
#endif