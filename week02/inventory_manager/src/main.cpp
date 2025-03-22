#include "database/Database.h"
#include "managers/InventoryManager.h"

#include "models/Department.h"
#include "models/Product.h"
#include "models/SKUInventory.h"
#include "models/PerishableItem.h"
#include "models/WarrantyItem.h"

#include <iostream>
#include <vector>

int main() {
    std::string dbPath = "data/inventory.db";
    Database db(dbPath);

    if (!db.databaseExists()) {
        std::cout << "Database not found. Creating new database...\n";
        db.initializeDatabase();
        db.open();
    } else {
        std::cout << "Database found. Connecting...\n";
        db.open();
    }

    InventoryManager manager(db);

    // Add Departments to DB
    db.insertDepartment("Grocery");
    db.insertDepartment("Electronics");
    db.insertDepartment("Kitchen");

    // Add Products
    std::vector<Product> products = {
        Product(0, "Organic Milk", "Grocery", "Dairy"),
        Product(0, "Eggs", "Grocery", "Dairy"),
        Product(0, "LED Tv", "Electronics", "Entertainment"),
        Product(0, "Blender", "Kitchen", "Appliances")
    };

    for (auto& product : products) {
        manager.addProduct(product);
    }

    // Add Inventory items
    std::vector<InventoryItem> items = {
        InventoryItem(0, "MILK-ORG-1GAL", "Organic Milk", "Grocery", 30, 5.99, "DairyCo"),
        InventoryItem(0, "EGGS-LRG-12CT", "Eggs", "Grocery", 45, 3.49, "FarmFresh"),
        InventoryItem(0, "TV-LED-42IN", "LED TV", "Electronics", 10, 299.99, "ElectroWorld"),
        InventoryItem(0, "BLENDER-PRO", "Blender", "Kitchen", 15, 89.99, "HomeChef")
    };

    for (auto& item : items) {
        manager.addInventoryItem(item);
    }

    // Add Perishable Items
    std::vector<PerishableItem> perishables = {
        PerishableItem(0, "MILK-ORG-1GAL", "Organic Milk", "Grocery", 30, 5.99, "DairyCo", "LOT-001", "2025-06-01", 2.0, 8.0),
        PerishableItem(0, "EGGS-LRG-12CT", "Eggs", "Grocery", 45, 3.49, "FarmFresh", "LOT-002", "2025-05-15", 1.0, 5.0)
    };

    for (auto& p : perishables) {
        db.insertPerishableItem(
            p.getSKU(),
            p.getLotNumber(),
            p.getExpirationDate(),
            p.getStorageTempMinCelsius(),
            p.getStorageTempMaxCelsius()
        );
    }

    // Warrantied items
    std::vector<WarrantyItem> warrantied = {
        WarrantyItem(0, "TV-LED-42IN", "LED TV", "Electronics", 10, 299.99, "ElectroWorld", "SN-TV001", "Manufacturer", "ElectroWorld", 0.0, 24, "Months"),
        WarrantyItem(0, "BLENDER-PRO", "Blender", "Kitchen", 15, 89.99, "HomeChef", "SN-BLND001", "Full", "HomeChef", 10.0, 12, "Months")
    };

    for (auto& w : warrantied) {
        db.insertWarrantyItem(
            w.getSKU(),
            w.getSerialNumber(),
            w.getWarrantyType(),
            w.getProvider(),
            w.getWarrantyPrice(),
            w.getWarrantyDuration(),
            w.getWarrantyDurationPeriod()
        );
    }

    std::cout << "\n✅ Inventory successfully loaded into the database!\n";
    db.close();
    
    return 0;
}