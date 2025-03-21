#include "managers/InventoryManager.h"
#include <iostream>

InventoryManager::InventoryManager(Database& dbInstance) : db(dbInstance) {}

// Add a new product to the database
bool InventoryManager::addProduct(const Product& product) {
    return db.insertProduct(product.getName(), product.getCategory(), product.getSubCategory());
}

// Fetch all products from the database
std::vector<Product> InventoryManager::getAllProducts() {
    return db.fetchAllProducts();
}

// Add a new SKU to the database
bool InventoryManager::addSKU(const SKUInventory& sku) {
    return db.insertSKUInventory(sku.getSKUID(), sku.getProductID(), sku.getPrice(), sku.getSupplier());
}

// Fetch all SKUs
std::vector<SKUInventory> InventoryManager::getAllSKUs() {
    return db.fetchAllSKUs();
}

// Add inventory stock
bool InventoryManager::addInventoryItem(const InventoryItem& item) {
    return db.insertInventoryItem(item.getSKU(), item.getQuantity(), "Each", 1);
}

// Fetch all inventory stock
std::vector<InventoryItem> InventoryManager::getAllInventoryItems() {
    return db.fetchAllInventoryItems();
}

// Display all inventory with SKU and quantity
void InventoryManager::displayAllInventory() {
    auto items = getAllInventoryItems();
    std::cout << "\n--- Inventory List ---\n";
    for (const auto& item : items) {
        item.displayItem();
        std::cout << "--------------------------\n";
    }
}