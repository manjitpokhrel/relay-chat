#ifndef BASEENTITY_H
#define BASEENTITY_H

#include <string>

class BaseEntity {
protected:
    int id;

public:
    BaseEntity(int id) : id(id) {}
    virtual ~BaseEntity() = default;
    virtual int getID() const { return id; }
    virtual std::string toString() const = 0;
};

#endif