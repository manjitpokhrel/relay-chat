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
