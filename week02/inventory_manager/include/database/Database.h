#ifndef DATABASE_H
#define DATABASE_H

#include "models/Department.h"
#include "models/Product.h"
#include "models/SKUInventory.h"
#include "models/InventoryItem.h"

#include <sqlite3.h>
#include <string>
#include <vector>

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

    // DB Insertions
    bool insertDepartment(const std::string& name);
    bool insertProduct(const std::string& name, const std::string& category, const std::string& subCategory);
    bool insertSKUInventory(const std::string& sku, int productID, double price, const std::string& supplier);
    bool insertInventoryItem(const std::string& sku, int quantity, const std::string& unitOfMeasure, int conversionFactor);
    bool insertPerishableItem(const std::string& sku, const std::string& lotNumber, const std::string& expirationDate, double minTemp, double maxTemp);
    bool insertWarrantyItem(const std::string& sku, const std::string& serialNumber, const std::string& type, const std::string& provider, double price, int duration, const std::string& period);

    // DB Queries
    // Queries
    std::vector<Department> fetchAllDepartments();
    std::vector<Product> fetchAllProducts();
    std::vector<SKUInventory> fetchAllSKUs();
    std::vector<InventoryItem> fetchAllInventoryItems();
    void queryPerishableItems();
    void queryWarrantiedItems();
};

#endif // DATABASE_H