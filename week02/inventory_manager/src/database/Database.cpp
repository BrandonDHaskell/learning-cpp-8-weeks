#include "Database.h"
#include <iostream>
#include <filesystem>

Database::Database(const std::string& path) : db(nullptr), dbPath(path) {}

Database::~Database() {
    close();
}

bool Database::open() {
    if (sqlite3_open(dbPath.c_str(), &db) == SQLITE_OK) {
        return true;
    } else {
        std::cerr << "Error opening database: " << sqlite3_errmsg(db) << std::endl;
        return false;
    }
}

void Database::close() {
    if (db) {
        sqlite3_close(db);
        db = nullptr;
    }
}

bool Database::databaseExists() {
    return std::filesystem::exists(dbPath);
}

void Database::initializeDatabase() {
    if (!open()) return;

    const char* createTablesQuery = R"(
        CREATE TABLE IF NOT EXISTS products (
            productID INTEGER PRIMARY KEY AUTOINCREMENT,
            name TEXT NOT NULL,
            category TEXT NOT NULL,
            subCategory TEXT
        );

        CREATE TABLE IF NOT EXISTS inventory_items (
            unitID INTEGER PRIMARY KEY AUTOINCREMENT,
            productID INTEGER NOT NULL,
            quantity INTEGER NOT NULL,
            unitOfMeasure TEXT NOT NULL CHECK (unitOfMeasure IN ('Each', 'Case')),
            conversionFactor INTEGER CHECK (conversionFactor > 0),
            FOREIGN KEY (productID) REFERENCES products(productID) ON DELETE CASCADE
        );

        CREATE TABLE IF NOT EXISTS sku_inventory (
            skuID TEXT PRIMARY KEY,
            productID INTEGER NOT NULL,
            price REAL NOT NULL,
            supplier TEXT NOT NULL,
            FOREIGN KEY (productID) REFERENCES products(productID) ON DELETE CASCADE
        );

        CREATE TABLE IF NOT EXISTS expiry_items (
            expiryID INTEGER PRIMARY KEY AUTOINCREMENT,
            skuID TEXT NOT NULL,
            lotNumber TEXT NOT NULL,
            lotExpirationDate TEXT NOT NULL,
            storageTempMinCelsius REAL NOT NULL,
            storageTempMaxCelsius REAL NOT NULL,
            FOREIGN KEY (skuID) REFERENCES sku_inventory(skuID) ON DELETE CASCADE
        );

        CREATE TABLE IF NOT EXISTS warranty_items (
            warrantyID INTEGER PRIMARY KEY AUTOINCREMENT,
            skuID TEXT NOT NULL,
            serialNumber TEXT NOT NULL UNIQUE,
            warrantyType TEXT CHECK (warrantyType IN ('Limited', 'Full', 'Manufacturer')) NOT NULL,
            provider TEXT NOT NULL,
            price REAL,
            duration INTEGER NOT NULL,
            durationPeriod TEXT CHECK (durationPeriod IN ('Days', 'Months', 'Years')) NOT NULL,
            FOREIGN KEY (skuID) REFERENCES sku_inventory(skuID) ON DELETE CASCADE
        );

        CREATE TABLE IF NOT EXISTS suppliers (
            supplierID INTEGER PRIMARY KEY AUTOINCREMENT,
            supplierName TEXT NOT NULL,
            phoneNumber TEXT,
            email TEXT,
            streetAddress TEXT,
            stateProvince TEXT,
            city TEXT,
            zip TEXT
        );

        CREATE TABLE IF NOT EXISTS supplier_products (
            supplierID INTEGER NOT NULL,
            productID INTEGER NOT NULL,
            quantityPerCase INTEGER NOT NULL CHECK (quantityPerCase > 0),
            caseCost REAL NOT NULL,
            PRIMARY KEY (supplierID, productID),
            FOREIGN KEY (supplierID) REFERENCES suppliers(supplierID) ON DELETE CASCADE,
            FOREIGN KEY (productID) REFERENCES products(productID) ON DELETE CASCADE
        );

        CREATE TABLE IF NOT EXISTS case_breakage_log (
            breakageID INTEGER PRIMARY KEY AUTOINCREMENT,
            skuID TEXT NOT NULL,
            casesConverted INTEGER NOT NULL CHECK (casesConverted > 0),
            eachesGenerated INTEGER NOT NULL CHECK (eachesGenerated > 0),
            breakageDate TEXT NOT NULL DEFAULT CURRENT_TIMESTAMP,
            FOREIGN KEY (skuID) REFERENCES sku_inventory(skuID) ON DELETE CASCADE
        );
    )";

    char* errorMessage = nullptr;
    if (sqlite3_exec(db, createTablesQuery, nullptr, nullptr, &errorMessage) != SQLITE_OK) {
        std::cerr << "Error initializing database: " << errorMessage << std::endl;
        sqlite3_free(errorMessage);
    } else {
        std::cout << "Database initialized successfully.\n";
    }

    close();
}
