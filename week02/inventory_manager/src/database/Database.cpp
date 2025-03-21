#include "database/Database.h"
#include <iostream>
#include <filesystem>

Database::Database(const std::string& path) : db(nullptr), dbPath(path) {}

Database::~Database() {
    close();
}

bool Database::databaseExists() {
    return std::filesystem::exists(dbPath);
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

bool Database::insertProduct(const std::string& name, const std::string& category, const std::string& subCategory) {
    if (!open()) return false;

    const char* sql = "INSERT INTO products (name, category, subCategory) VALUES (?, ?, ?);";
    sqlite3_stmt* stmt;

    if (sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr) != SQLITE_OK) {
        std::cerr << "Failed to prepare insertProduct: " << sqlite3_errmsg(db) << "\n";
        return false;
    }

    sqlite3_bind_text(stmt, 1, name.c_str(), -1, SQLITE_TRANSIENT);
    sqlite3_bind_text(stmt, 2, category.c_str(), -1, SQLITE_TRANSIENT);
    sqlite3_bind_text(stmt, 3, subCategory.c_str(), -1, SQLITE_TRANSIENT);

    bool success = (sqlite3_step(stmt) == SQLITE_DONE);

    if (!success) {
        std::cerr << "insertProduct failed: " << sqlite3_errmsg(db) << "\n";
    }

    sqlite3_finalize(stmt);
    close();
    return success;
}

bool Database::insertSKUInventory(const std::string& sku, int productID, double price, const std::string& supplier) {
    if (!open()) return false;
    const char* sql = "INSERT INTO sku_inventory (skuID, productID, price, supplier) VALUES (?, ?, ?, ?);";
    sqlite3_stmt* stmt;

    if (sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr) != SQLITE_OK) return false;
    sqlite3_bind_text(stmt, 1, sku.c_str(), -1, SQLITE_TRANSIENT);
    sqlite3_bind_int(stmt, 2, productID);
    sqlite3_bind_double(stmt, 3, price);
    sqlite3_bind_text(stmt, 4, supplier.c_str(), -1, SQLITE_TRANSIENT);

    bool success = sqlite3_step(stmt) == SQLITE_DONE;
    sqlite3_finalize(stmt);
    close();
    return success;
}

bool Database::insertInventoryItem(const std::string& sku, int quantity, const std::string& unitOfMeasure, int conversionFactor) {
    if (!open()) return false;
    const char* sql = "INSERT INTO inventory_items (skuID, quantity, unitOfMeasure, conversionFactor) VALUES (?, ?, ?, ?);";
    sqlite3_stmt* stmt;

    if (sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr) != SQLITE_OK) return false;
    sqlite3_bind_text(stmt, 1, sku.c_str(), -1, SQLITE_TRANSIENT);
    sqlite3_bind_int(stmt, 2, quantity);
    sqlite3_bind_text(stmt, 3, unitOfMeasure.c_str(), -1, SQLITE_TRANSIENT);
    sqlite3_bind_int(stmt, 4, conversionFactor);

    bool success = sqlite3_step(stmt) == SQLITE_DONE;
    sqlite3_finalize(stmt);
    close();
    return success;
}

bool Database::insertPerishableItem(const std::string& sku, const std::string& lotNumber, const std::string& expirationDate, double minTemp, double maxTemp) {
    if (!open()) return false;
    const char* sql = "INSERT INTO expiry_items (skuID, lotNumber, lotExpirationDate, storageTempMinCelsius, storageTempMaxCelsius) VALUES (?, ?, ?, ?, ?);";
    sqlite3_stmt* stmt;

    if (sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr) != SQLITE_OK) return false;
    sqlite3_bind_text(stmt, 1, sku.c_str(), -1, SQLITE_TRANSIENT);
    sqlite3_bind_text(stmt, 2, lotNumber.c_str(), -1, SQLITE_TRANSIENT);
    sqlite3_bind_text(stmt, 3, expirationDate.c_str(), -1, SQLITE_TRANSIENT);
    sqlite3_bind_double(stmt, 4, minTemp);
    sqlite3_bind_double(stmt, 5, maxTemp);

    bool success = sqlite3_step(stmt) == SQLITE_DONE;
    sqlite3_finalize(stmt);
    close();
    return success;
}

std::vector<Product> Database::fetchAllProducts() {
    std::vector<Product> products;
    if (!open()) return products;

    const char* sql = "SELECT productID, name, category, subCategory FROM products";
    sqlite3_stmt* stmt;

    if (sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr) == SQLITE_OK) {
        while (sqlite3_step(stmt) == SQLITE_ROW) {
            int id = sqlite3_column_int(stmt, 0);
            std::string name = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1));
            std::string category = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 2));
            std::string subCategory = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 3));
            products.emplace_back(id, name, category, subCategory);
        }
    } else {
        std::cerr << "Failed to fetch products: " << sqlite3_errmsg(db) << std::endl;
    }

    sqlite3_finalize(stmt);
    close();
    return products;
}

std::vector<SKUInventory> Database::fetchAllSKUs() {
    std::vector<SKUInventory> skus;
    if (!open()) return skus;

    const char* sql = "SELECT skuID, productID, price, supplier FROM sku_inventory";
    sqlite3_stmt* stmt;

    if (sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr) == SQLITE_OK) {
        while (sqlite3_step(stmt) == SQLITE_ROW) {
            std::string skuID = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 0));
            int productID = sqlite3_column_int(stmt, 1);
            double price = sqlite3_column_double(stmt, 2);
            std::string supplier = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 3));
            skus.emplace_back(skuID, productID, price, supplier);
        }
    } else {
        std::cerr << "Failed to fetch SKUs: " << sqlite3_errmsg(db) << std::endl;
    }

    sqlite3_finalize(stmt);
    close();
    return skus;
}

std::vector<InventoryItem> Database::fetchAllInventoryItems() {
    std::vector<InventoryItem> items;
    if (!open()) return items;

    const char* sql = R"(
        SELECT ii.unitID, ii.skuID, p.name, p.category, ii.quantity, si.price, si.supplier
        FROM inventory_items ii
        JOIN sku_inventory si ON ii.skuID = si.skuID
        JOIN products p ON si.productID = p.productID
    )";

    sqlite3_stmt* stmt;

    if (sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr) == SQLITE_OK) {
        while (sqlite3_step(stmt) == SQLITE_ROW) {
            int itemID = sqlite3_column_int(stmt, 0);
            std::string skuID = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1));
            std::string name = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 2));
            std::string category = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 3));
            int quantity = sqlite3_column_int(stmt, 4);
            double price = sqlite3_column_double(stmt, 5);
            std::string supplier = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 6));
            items.emplace_back(itemID, skuID, name, category, quantity, price, supplier);
        }
    } else {
        std::cerr << "Failed to fetch inventory items: " << sqlite3_errmsg(db) << std::endl;
    }

    sqlite3_finalize(stmt);
    close();
    return items;
}
