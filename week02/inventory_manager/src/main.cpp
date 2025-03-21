#include <iostream>
#include "database/Database.h"

int main() {
    std::string dbPath = "data/inventory.db";
    Database db(dbPath);

    if (!db.databaseExists()) {
        std::cout << "Database not found. Creating new database...\n";
        db.initializeDatabase();
    } else {
        std::cout << "Database found. Connecting...\n";
        db.open();
    }
    return 0;
}