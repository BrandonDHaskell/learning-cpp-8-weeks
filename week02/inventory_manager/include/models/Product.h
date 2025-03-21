#ifndef PRODUCT_H
#define PRODUCT_H

#include <string>

class Product {
private:
    int productID;              // Unique ID in the database
    std::string name;           // Product name (e.g. "Organic Milk")
    std::string category;       // Category (e.g. "Grocery")
    std::string subCategory;    // Sub-category (e.g. "Dairy")

public:
    // Constructors
    Product();
    Product(int id, const std::string& name, const std::string& category, const std::string& subCategory);

    // Getters
    int getProductID() const;
    std::string getName() const;
    std::string getCategory() const;
    std::string getSubCategory() const;

    // Setters
    void setProductID(int id);
    void setName(const std::string& name);
    void setCategory(const std::string& category);
    void setSubCategory(const std::string& subCategory);

    // Utility
    void display() const;
};

#endif // PRODUCT_H