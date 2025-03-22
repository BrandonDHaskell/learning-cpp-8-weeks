#include "models/PerishableItem.h"

PerishableItem::PerishableItem(int id, const std::string& sku, const std::string& name,
                               const std::string& category, int qty, double price,
                               const std::string& supplier, const std::string& lot,
                               const std::string& expDate, double minTemp, double maxTemp)
    : InventoryItem(id, sku, name, category, qty, price, supplier),
      lotNumber(lot), expirationDate(expDate),
      storageTempMin(minTemp), storageTempMax(maxTemp) {}

std::string PerishableItem::getLotNumber() const { return lotNumber; }
std::string PerishableItem::getExpirationDate() const { return expirationDate; }
double PerishableItem::getStorageTempMinCelsius() const { return storageTempMin; }
double PerishableItem::getStorageTempMaxCelsius() const { return storageTempMax; }

void PerishableItem::setLotNumber(const std::string& lot) { lotNumber = lot; }
void PerishableItem::setExpirationDate(const std::string& date) { expirationDate = date; }
void PerishableItem::setStorageTempMinCelsius(double temp) { storageTempMin = temp; }
void PerishableItem::setStorageTempMaxCelsius(double temp) { storageTempMax = temp; }