#include "models/Product.h"
#include <iostream>

// Default constructor
Product::Product()
    : productID(0), name(""), category(""), subCategory("") {}

// Parameterized constructor
Product::Product(int id, const std::string& name, const std::string& category, const std::string& subCategory)
    : productID(id), name(name), category(category), subCategory(subCategory) {}

// Getters
int Product::getProductID() const { return productID; }
std::string Product::getName() const { return name; }
std::string Product::getCategory() const { return category; }
std::string Product::getSubCategory() const { return subCategory; }

// Setters
void Product::setProductID(int id) { productID = id; }
void Product::setName(const std::string& newName) { name = newName; }
void Product::setCategory(const std::string& newCategory) { category = newCategory; }
void Product::setSubCategory(const std::string& newSubCategory) { subCategory = newSubCategory; }

// Display utility
void Product::display() const {
    std::cout << "Product ID: " << productID << std::endl;
    std::cout << "Name: " << name << std::endl;
    std::cout << "Category: " << category << std::endl;
    std::cout << "Subcategory: " << subCategory << std::endl;
}