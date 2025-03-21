#ifndef INVENTORY_ITEM_H
#define INVENTORY_ITEM_H

#include <string>
#include <iostream>

class InventoryItem {
protected:
    int itemID;             // Unique database ID for the item
    std::string SKU;        // Unique SKU for tracking
    std::string name;       // Item name
    std::string category;   // Product category (e.g., Electronics, Grocery)
    int quantity;           // Number of items in stock
    double price;           // Price per unit
    std::string supplier;   // Supplier name

public:
    // Constructor
    InventoryItem(int id, const std::string& sku, const std::string& name, 
                  const std::string& category, int qty, double price, 
                  const std::string& supplier);

    // Virtual destructor (important for inheritance)
    virtual ~InventoryItem() {}

    // Getters
    int getItemID() const;
    std::string getSKU() const;
    std::string getName() const;
    std::string getCategory() const;
    int getQuantity() const;
    double getPrice() const;
    std::string getSupplier() const;

    // Setters
    void setQuantity(int qty);
    void setPrice(double price);

    // Virtual function for displaying item details
    virtual void displayItem() const;

    // Virtual function for serialization (for database storage)
    virtual std::string serialize() const;
};

#endif // INVENTORY_ITEM_H