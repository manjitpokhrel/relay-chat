#include "ServerDB.h"
#include <iostream>
#include <sstream>

ServerDB::ServerDB(
    const std::string& host,
    const std::string& dbname,
    const std::string& user,
    const std::string& password,
    int port) {

    std::string connStr =
        "host=" + host +
        " dbname=" + dbname +
        " user=" + user +
        " password=" + password +
        " port=" + std::to_string(port);

    conn = PQconnectdb(connStr.c_str());

    if (PQstatus(conn) != CONNECTION_OK) {
        std::cerr << "DB Connection failed: "
                  << PQerrorMessage(conn) << "\n";
        PQfinish(conn);
        conn = nullptr;
    } else {
        std::cout << "DB Connected.\n";
        initSchema();
    }
}

ServerDB::~ServerDB() {
    if (conn) PQfinish(conn);
}

bool ServerDB::isConnected() const {
    return conn && PQstatus(conn) == CONNECTION_OK;
}

PGresult* ServerDB::execute(
    const std::string& query) {
    return PQexec(conn, query.c_str());
}

PGresult* ServerDB::executeParams(
    const std::string& query,
    int nParams,
    const char* const* values) {
    return PQexecParams(
        conn, query.c_str(),
        nParams, nullptr, values,
        nullptr, nullptr, 0);
}

void ServerDB::initSchema() {
    execute(
        "CREATE TABLE IF NOT EXISTS users ("
        "id SERIAL PRIMARY KEY,"
        "username VARCHAR(50) UNIQUE NOT NULL,"
        "password_hash VARCHAR(255) NOT NULL,"
        "status VARCHAR(20) DEFAULT 'offline',"
        "created_at TIMESTAMP DEFAULT NOW())"
    );
    execute(
        "CREATE TABLE IF NOT EXISTS rooms ("
        "id SERIAL PRIMARY KEY,"
        "name VARCHAR(100) UNIQUE NOT NULL,"
        "created_by INTEGER REFERENCES users(id),"
        "created_at TIMESTAMP DEFAULT NOW())"
    );
    execute(
        "CREATE TABLE IF NOT EXISTS messages ("
        "id SERIAL PRIMARY KEY,"
        "room_id INTEGER REFERENCES rooms(id),"
        "user_id INTEGER REFERENCES users(id),"
        "sender_name VARCHAR(50) NOT NULL,"
        "content TEXT NOT NULL,"
        "timestamp TIMESTAMP DEFAULT NOW())"
    );
    execute(
        "CREATE TABLE IF NOT EXISTS members ("
        "room_id INTEGER REFERENCES rooms(id),"
        "user_id INTEGER REFERENCES users(id),"
        "PRIMARY KEY (room_id, user_id))"
    );
    std::cout << "Schema initialized.\n";
}

bool ServerDB::registerUser(
    const std::string& username,
    const std::string& passwordHash) {
    const char* values[] = {
        username.c_str(),
        passwordHash.c_str()
    };
    PGresult* res = executeParams(
        "INSERT INTO users (username, password_hash) "
        "VALUES ($1, $2)",
        2, values);
    bool ok = PQresultStatus(res) == PGRES_COMMAND_OK;
    PQclear(res);
    return ok;
}

int ServerDB::loginUser(
    const std::string& username,
    const std::string& passwordHash) {
    const char* values[] = {
        username.c_str(),
        passwordHash.c_str()
    };
    PGresult* res = executeParams(
        "SELECT id FROM users "
        "WHERE username=$1 AND password_hash=$2",
        2, values);
    int userID = -1;
    if (PQntuples(res) > 0) {
        userID = std::stoi(PQgetvalue(res, 0, 0));
    }
    PQclear(res);
    return userID;
}

int ServerDB::createRoom(
    const std::string& name,
    int createdBy) {
    std::string cb = std::to_string(createdBy);
    const char* values[] = {
        name.c_str(),
        cb.c_str()
    };
    PGresult* res = executeParams(
        "INSERT INTO rooms (name, created_by) "
        "VALUES ($1, $2) RETURNING id",
        2, values);
    int roomID = -1;
    if (PQresultStatus(res) == PGRES_TUPLES_OK &&
        PQntuples(res) > 0) {
        roomID = std::stoi(PQgetvalue(res, 0, 0));
        joinRoom(createdBy, roomID);
    }
    PQclear(res);
    return roomID;
}

bool ServerDB::joinRoom(int userID, int roomID) {
    std::string uid = std::to_string(userID);
    std::string rid = std::to_string(roomID);
    const char* values[] = {
        rid.c_str(),
        uid.c_str()
    };
    PGresult* res = executeParams(
        "INSERT INTO members (room_id, user_id) "
        "VALUES ($1, $2) ON CONFLICT DO NOTHING",
        2, values);
    bool ok = PQresultStatus(res) == PGRES_COMMAND_OK;
    PQclear(res);
    return ok;
}

std::string ServerDB::getAllRoomsJSON() {
    PGresult* res = execute(
        "SELECT id, name, created_by FROM rooms "
        "ORDER BY created_at ASC");
    std::ostringstream json;
    json << "[";
    int rows = PQntuples(res);
    for (int i = 0; i < rows; i++) {
        if (i > 0) json << ",";
        json << "{"
             << "\"id\":" << PQgetvalue(res, i, 0)
             << ","
             << "\"name\":\""
             << PQgetvalue(res, i, 1) << "\","
             << "\"createdBy\":"
             << PQgetvalue(res, i, 2)
             << "}";
    }
    json << "]";
    PQclear(res);
    return json.str();
}

bool ServerDB::saveMessage(
    int roomID, int userID,
    const std::string& senderName,
    const std::string& content) {
    std::string rid = std::to_string(roomID);
    std::string uid = std::to_string(userID);
    const char* values[] = {
        rid.c_str(), uid.c_str(),
        senderName.c_str(), content.c_str()
    };
    PGresult* res = executeParams(
        "INSERT INTO messages "
        "(room_id, user_id, sender_name, content) "
        "VALUES ($1, $2, $3, $4)",
        4, values);
    bool ok = PQresultStatus(res) == PGRES_COMMAND_OK;
    PQclear(res);
    return ok;
}

std::string ServerDB::getMessagesJSON(int roomID) {
    std::string rid = std::to_string(roomID);
    const char* values[] = { rid.c_str() };
    PGresult* res = executeParams(
        "SELECT id, room_id, user_id, sender_name, "
        "content, "
        "TO_CHAR(timestamp, 'YYYY-MM-DD HH24:MI:SS') "
        "FROM messages WHERE room_id=$1 "
        "ORDER BY timestamp ASC",
        1, values);
    std::ostringstream json;
    json << "[";
    int rows = PQntuples(res);
    for (int i = 0; i < rows; i++) {
        if (i > 0) json << ",";
        json << "{"
             << "\"id\":" << PQgetvalue(res, i, 0)
             << ","
             << "\"roomID\":" << PQgetvalue(res, i, 1)
             << ","
             << "\"userID\":" << PQgetvalue(res, i, 2)
             << ","
             << "\"senderName\":\""
             << PQgetvalue(res, i, 3) << "\","
             << "\"content\":\""
             << PQgetvalue(res, i, 4) << "\","
             << "\"timestamp\":\""
             << PQgetvalue(res, i, 5) << "\""
             << "}";
    }
    json << "]";
    PQclear(res);
    return json.str();
}

bool ServerDB::clearMessages(int roomID) {
    std::string rid = std::to_string(roomID);
    const char* values[] = { rid.c_str() };
    PGresult* res = executeParams(
        "DELETE FROM messages WHERE room_id=$1",
        1, values);
    bool ok = PQresultStatus(res) == PGRES_COMMAND_OK;
    PQclear(res);
    return ok;
}