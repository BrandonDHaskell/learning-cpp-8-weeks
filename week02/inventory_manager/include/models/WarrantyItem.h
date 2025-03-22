#ifndef WARRANTY_ITEM_H
#define WARRANTY_ITEM_H

#include "models/InventoryItem.h"
#include "interfaces/IWarrantied.h"

class WarrantyItem : public InventoryItem, public IWarrantied {
private:
    std::string serialNumber;
    std::string warrantyType;
    std::string provider;
    double warrantyPrice;
    int warrantyDuration;
    std::string warrantyDurationPeriod;

public:
    WarrantyItem(int id, const std::string& sku, const std::string& name, 
                 const std::string& category, int qty, double price, 
                 const std::string& supplier, const std::string& serial, 
                 const std::string& type, const std::string& provider, 
                 double priceWarranty, int duration, const std::string& period);

    // Implement IWarrantied interface
    std::string getSerialNumber() const override;
    std::string getWarrantyType() const override;
    std::string getProvider() const override;
    double getWarrantyPrice() const override;
    int getWarrantyDuration() const override;
    std::string getWarrantyDurationPeriod() const override;

    void setSerialNumber(const std::string& serial) override;
    void setWarrantyType(const std::string& type) override;
    void setProvider(const std::string& provider) override;
    void setWarrantyPrice(double price) override;
    void setWarrantyDuration(int duration) override;
    void setWarrantyDurationPeriod(const std::string& period) override;
};

#endif // WARRANTY_ITEM_H