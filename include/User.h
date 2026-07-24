#pragma once
#ifndef USER_H
#define USER_H

#include "BaseEntity.h"
#include <string>

class User : public BaseEntity {
private:
    std::string username;
    std::string passwordHash;
    std::string status;

public:
    User(int id, const std::string& username,
         const std::string& passwordHash,
         const std::string& status = "online")
        : BaseEntity(id),
          username(username),
          passwordHash(passwordHash),
          status(status) {}

    std::string getUsername() const { return username; }
    std::string getPasswordHash() const { return passwordHash; }
    std::string getStatus() const { return status; }
    void setStatus(const std::string& s) { status = s; }

    std::string toString() const override {
        return "User[" + std::to_string(id) + "]: " + username;
    }
};

#endif