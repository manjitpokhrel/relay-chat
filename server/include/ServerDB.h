#ifndef SERVERDB_H
#define SERVERDB_H

#include <string>
#include <libpq-fe.h> // PostgreSQL C client library header

class ServerDB {
public:
    ServerDB(
        const std::string& host,
        const std::string& dbname,
        const std::string& user,
        const std::string& password,
        int port
    );
    ~ServerDB();

    bool isConnected() const;
    
    PGresult* execute(const std::string& query);
    
    PGresult* executeParams(
        const std::string& query,
        int nParams,
        const char* const* values
    );

    void initSchema();

    bool registerUser(const std::string& username, const std::string& passwordHash);
    int loginUser(const std::string& username, const std::string& passwordHash);
    
    int createRoom(const std::string& name, int createdBy);
    bool joinRoom(int userID, int roomID);
    
    std::string getAllRoomsJSON();
    
    bool saveMessage(
        int roomID, int userID,
        const std::string& senderName,
        const std::string& content
    );
    
    std::string getMessagesJSON(int roomID);
    bool clearMessages(int roomID);

private:
    PGconn* conn; // PostgreSQL connection handle
};

#endif // SERVERDB_H