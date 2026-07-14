#include "DatabaseManager.h"
#include <QVariant>

DatabaseManager::DatabaseManager(const QString& dbPath) {
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName(dbPath);

    if (!db.open()) {
        qDebug() << "Database error:" << db.lastError().text();
        return;
    }

    initializeTables();
    qDebug() << "Database connected.";
}

DatabaseManager::~DatabaseManager() {
    if (db.isOpen()) db.close();
}

void DatabaseManager::initializeTables() {
    QSqlQuery query;

    query.exec(
        "CREATE TABLE IF NOT EXISTS users ("
        "id INTEGER PRIMARY KEY AUTOINCREMENT,"
        "username TEXT UNIQUE NOT NULL,"
        "password_hash TEXT NOT NULL,"
        "created_at DATETIME DEFAULT CURRENT_TIMESTAMP)"
    );

    query.exec(
        "CREATE TABLE IF NOT EXISTS rooms ("
        "id INTEGER PRIMARY KEY AUTOINCREMENT,"
        "name TEXT UNIQUE NOT NULL,"
        "created_by INTEGER REFERENCES users(id),"
        "created_at DATETIME DEFAULT CURRENT_TIMESTAMP)"
    );

    query.exec(
        "CREATE TABLE IF NOT EXISTS messages ("
        "id INTEGER PRIMARY KEY AUTOINCREMENT,"
        "room_id INTEGER REFERENCES rooms(id),"
        "user_id INTEGER REFERENCES users(id),"
        "sender_name TEXT NOT NULL,"
        "content TEXT NOT NULL,"
        "timestamp DATETIME DEFAULT CURRENT_TIMESTAMP)"
    );

    query.exec(
        "CREATE TABLE IF NOT EXISTS members ("
        "room_id INTEGER REFERENCES rooms(id),"
        "user_id INTEGER REFERENCES users(id),"
        "PRIMARY KEY (room_id, user_id))"
    );
}
<<<<<<< HEAD

=======
>>>>>>> 70d55099947c2fb834270d18a27649e7a233efd5
bool DatabaseManager::registerUser(const std::string& username,
                                    const std::string& password) {
    QSqlQuery query;
    query.prepare(
        "INSERT INTO users (username, password_hash) VALUES (?, ?)"
    );
    query.addBindValue(QString::fromStdString(username));
    query.addBindValue(QString::fromStdString(password));

    if (!query.exec()) {
        qDebug() << "Register error:" << query.lastError().text();
        return false;
    }
    return true;
}
<<<<<<< HEAD

=======
>>>>>>> 70d55099947c2fb834270d18a27649e7a233efd5
std::shared_ptr<User> DatabaseManager::loginUser(
    const std::string& username,
    const std::string& password) {

    QSqlQuery query;
    query.prepare(
        "SELECT id, username, password_hash FROM users "
        "WHERE username = ? AND password_hash = ?"
    );
    query.addBindValue(QString::fromStdString(username));
    query.addBindValue(QString::fromStdString(password));

    if (query.exec() && query.next()) {
        int id = query.value(0).toInt();
        std::string uname = query.value(1).toString().toStdString();
        std::string hash = query.value(2).toString().toStdString();
        return std::make_shared<User>(id, uname, hash);
    }
    return nullptr;
}

bool DatabaseManager::createRoom(const std::string& name,
                                  int userID) {
    QSqlQuery query;
    query.prepare(
        "INSERT INTO rooms (name, created_by) VALUES (?, ?)"
    );
    query.addBindValue(QString::fromStdString(name));
    query.addBindValue(userID);

    if (!query.exec()) {
        qDebug() << "Create room error:" << query.lastError().text();
        return false;
    }
<<<<<<< HEAD

    int roomID = query.lastInsertId().toInt();
    return joinRoom(userID, roomID);
}

std::vector<std::shared_ptr<Room>> DatabaseManager::getAllRooms() {
    std::vector<std::shared_ptr<Room>> rooms;
    QSqlQuery query("SELECT id, name, created_by FROM rooms");

    while (query.next()) {
        int id = query.value(0).toInt();
        std::string name = query.value(1).toString().toStdString();
        int createdBy = query.value(2).toInt();
        rooms.push_back(std::make_shared<Room>(id, name, createdBy));
    }
    return rooms;
}

bool DatabaseManager::joinRoom(int userID, int roomID) {
    QSqlQuery query;
    query.prepare(
        "INSERT OR IGNORE INTO members (room_id, user_id) "
        "VALUES (?, ?)"
    );
    query.addBindValue(roomID);
    query.addBindValue(userID);
    return query.exec();
}

bool DatabaseManager::saveMessage(int roomID, int userID,
                                   const std::string& content,
                                   const std::string& senderName) {
    QSqlQuery query;
    query.prepare(
        "INSERT INTO messages "
        "(room_id, user_id, sender_name, content) "
        "VALUES (?, ?, ?, ?)"
    );
    query.addBindValue(roomID);
    query.addBindValue(userID);
    query.addBindValue(QString::fromStdString(senderName));
    query.addBindValue(QString::fromStdString(content));

    if (!query.exec()) {
        qDebug() << "Save message error:" << query.lastError().text();
        return false;
    }
    return true;
}

std::vector<std::shared_ptr<Message>>
DatabaseManager::getMessages(int roomID) {
    std::vector<std::shared_ptr<Message>> messages;

    QSqlQuery query;
    query.prepare(
        "SELECT id, room_id, user_id, sender_name, "
        "content, timestamp "
        "FROM messages WHERE room_id = ? "
        "ORDER BY timestamp ASC"
    );
    query.addBindValue(roomID);

    if (query.exec()) {
        while (query.next()) {
            int id = query.value(0).toInt();
            int rID = query.value(1).toInt();
            int uID = query.value(2).toInt();
            std::string senderName =
                query.value(3).toString().toStdString();
            std::string content =
                query.value(4).toString().toStdString();
            std::string timestamp =
                query.value(5).toString().toStdString();

            messages.push_back(
                std::make_shared<Message>(
                    id, rID, uID, senderName, content, timestamp
                )
            );
        }
    }
    return messages;
}

bool DatabaseManager::clearRoomMessages(int roomID) {
    QSqlQuery query;
    query.prepare("DELETE FROM messages WHERE room_id = ?");
    query.addBindValue(roomID);

    if (!query.exec()) {
        qDebug() << "Clear messages error:"
                 << query.lastError().text();
        return false;
    }
    return true;
}
=======
>>>>>>> 70d55099947c2fb834270d18a27649e7a233efd5
