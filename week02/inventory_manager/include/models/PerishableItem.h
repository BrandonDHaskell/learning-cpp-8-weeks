#ifndef PERISHABLE_ITEM_H
#define PERISHABLE_ITEM_H

#include "models/InventoryItem.h"
#include "interfaces/IPerishable.h"

class PerishableItem : public InventoryItem, public IPerishable {
private:
    std::string lotNumber;
    std::string expirationDate;
    double storageTempMin;
    double storageTempMax;

public:
    PerishableItem(int id, const std::string& sku, const std::string& name, 
                   const std::string& category, int qty, double price, 
                   const std::string& supplier, const std::string& lot, 
                   const std::string& expDate, double minTemp, double maxTemp);

    // Implement IPerishable interface
    std::string getLotNumber() const override;
    std::string getExpirationDate() const override;
    double getStorageTempMinCelsius() const override;
    double getStorageTempMaxCelsius() const override;

    void setLotNumber(const std::string& lot) override;
    void setExpirationDate(const std::string& date) override;
    void setStorageTempMinCelsius(double temp) override;
    void setStorageTempMaxCelsius(double temp) override;
};

#endif // PERISHABLE_ITEM_H