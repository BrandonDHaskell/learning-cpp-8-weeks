#include <iostream>
#include "database/Database.h"
#include "models/PerishableItem.h"
#include "models/WarrantyItem.h"
#include "models/Product.h"

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

    // Perishable item (milk) create and print object attributes
    PerishableItem milk(1, "MILK-ORG-1GAL", "Organic Milk", "Grocery", 50, 5.99, "DairyCo", "BATCH12345", "2025-06-01", 2.0, 8.0);
    std::cout << "Milk Expiration Date: " << milk.getExpirationDate() << std::endl;

    // Warrantied item (laptop) create and print object attributes
    WarrantyItem laptop(2, "LAPTOP-DELL-XPS13", "Dell XPS 13", "Electronics", 10, 1299.99, "Dell", "SN-987654", "Manufacturer", "Dell", 0.0, 24, "Months");
    std::cout << "Laptop Warranty: " << laptop.getWarrantyDuration() << " " << laptop.getWarrantyDurationPeriod() << std::endl;

    // Product item (p1) create and print object attributes
    Product p1(0, "Organix Milk", "Grocery", "Dairy");
    p1.display();

    return 0;
}