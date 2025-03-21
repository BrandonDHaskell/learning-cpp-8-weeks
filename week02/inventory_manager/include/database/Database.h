#ifndef DATABASE_H
#define DATABASE_H

#include <sqlite3.h>
#include <string>

class Database {
private:
    sqlite3* db;
    std::string dbPath;

public:
    Database(const std::string& path);
    ~Database();

    bool open();
    void close();
    bool databaseExists();
    void initializeDatabase();
};

#endif // DATABASE_H