#include "models/InventoryItem.h"

// Constructor
InventoryItem::InventoryItem(int id, const std::string& sku, const std::string& name, 
                             const std::string& category, int qty, double price, 
                             const std::string& supplier)
    : itemID(id), SKU(sku), name(name), category(category), quantity(qty), 
      price(price), supplier(supplier) {}

// Getters
int InventoryItem::getItemID() const { return itemID; }
std::string InventoryItem::getSKU() const { return SKU; }
std::string InventoryItem::getName() const { return name; }
std::string InventoryItem::getCategory() const { return category; }
int InventoryItem::getQuantity() const { return quantity; }
double InventoryItem::getPrice() const { return price; }
std::string InventoryItem::getSupplier() const { return supplier; }

// Setters
void InventoryItem::setQuantity(int qty) { 
    if (qty >= 0) quantity = qty; 
}

void InventoryItem::setPrice(double priceValue) { 
    if (priceValue >= 0) price = priceValue; 
}

// Display item details
void InventoryItem::displayItem() const {
    std::cout << "Item ID: " << itemID << "\n";
    std::cout << "SKU: " << SKU << "\n";
    std::cout << "Name: " << name << "\n";
    std::cout << "Category: " << category << "\n";
    std::cout << "Quantity: " << quantity << "\n";
    std::cout << "Price: $" << price << "\n";
    std::cout << "Supplier: " << supplier << "\n";
}

// Serialize data (for database storage)
std::string InventoryItem::serialize() const {
    return SKU + "|" + name + "|" + category + "|" + std::to_string(quantity) + "|" +
           std::to_string(price) + "|" + supplier;
}