#include "models/SKUInventory.h"
#include <iostream>

// Default constructor
SKUInventory::SKUInventory() : skuID(""), productID(0), price(0.0), supplier("") {}

// Parameterized constructor
SKUInventory::SKUInventory(const std::string& id, int prodID, double p, const std::string& s)
    : skuID(id), productID(prodID), price(p), supplier(s) {}

// Getters
std::string SKUInventory::getSKUID() const { return skuID; }
int SKUInventory::getProductID() const { return productID; }
double SKUInventory::getPrice() const { return price; }
std::string SKUInventory::getSupplier() const { return supplier; }

// Setters
void SKUInventory::setSKUID(const std::string& id) { skuID = id; }
void SKUInventory::setProductID(int id) { productID = id; }
void SKUInventory::setPrice(double p) { price = p; }
void SKUInventory::setSupplier(const std::string& s) { supplier = s; }

// Display
void SKUInventory::display() const {
    std::cout << "SKU ID: " << skuID << std::endl;
    std::cout << "Product ID: " << productID << std::endl;
    std::cout << "Price: $" << price << std::endl;
    std::cout << "Supplier: " << supplier << std::endl;
}