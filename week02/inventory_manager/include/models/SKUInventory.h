#ifndef SKU_INVENTORY_H
#define SKU_INVENTORY_H

#include <string>

class SKUInventory {
private:
    std::string skuID;        // Unique SKU identifier
    int productID;            // Foreign key reference to products table
    double price;             // Price per unit
    std::string supplier;     // Supplier name

public:
    // Constructors
    SKUInventory();
    SKUInventory(const std::string& skuID, int productID, double price, const std::string& supplier);

    // Getters
    std::string getSKUID() const;
    int getProductID() const;
    double getPrice() const;
    std::string getSupplier() const;

    // Setters
    void setSKUID(const std::string& id);
    void setProductID(int id);
    void setPrice(double p);
    void setSupplier(const std::string& s);

    // Display
    void display() const;
};

#endif // SKU_INVENTORY_H