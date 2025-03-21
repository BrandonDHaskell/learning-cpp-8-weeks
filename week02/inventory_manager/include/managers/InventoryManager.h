#ifndef INVENTORY_MANAGER_H
#define INVENTORY_MANAGER_H

#include <string>
#include <vector>
#include "models/Product.h"
#include "models/SKUInventory.h"
#include "models/InventoryItem.h"
#include "database/Database.h"

class InventoryManager {
private:
    Database& db;

public:
    explicit InventoryManager(Database& dbInstance);

    // Product-related
    bool addProduct(const Product& product);
    std::vector<Product> getAllProducts();

    // SKU-related
    bool addSKU(const SKUInventory& sku);
    std::vector<SKUInventory> getAllSKUs();

    // Inventory-related
    bool addInventoryItem(const InventoryItem& item);
    std::vector<InventoryItem> getAllInventoryItems();

    // Utility
    void displayAllInventory();
};

#endif // INVENTORY_MANAGER_H