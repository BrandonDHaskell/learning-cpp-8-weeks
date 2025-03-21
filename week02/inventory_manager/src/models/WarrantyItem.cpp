#include "models/WarrantyItem.h"

WarrantyItem::WarrantyItem(int id, const std::string& sku, const std::string& name,
                           const std::string& category, int qty, double price,
                           const std::string& supplier, const std::string& serial,
                           const std::string& type, const std::string& provider,
                           double priceWarranty, int duration, const std::string& period)
    : InventoryItem(id, sku, name, category, qty, price, supplier),
      serialNumber(serial), warrantyType(type), provider(provider),
      warrantyPrice(priceWarranty), warrantyDuration(duration),
      warrantyDurationPeriod(period) {}

std::string WarrantyItem::getSerialNumber() const { return serialNumber; }
std::string WarrantyItem::getWarrantyType() const { return warrantyType; }
std::string WarrantyItem::getProvider() const { return provider; }
double WarrantyItem::getWarrantyPrice() const { return warrantyPrice; }
int WarrantyItem::getWarrantyDuration() const { return warrantyDuration; }
std::string WarrantyItem::getWarrantyDurationPeriod() const { return warrantyDurationPeriod; }

void WarrantyItem::setSerialNumber(const std::string& serial) { serialNumber = serial; }
void WarrantyItem::setWarrantyType(const std::string& type) { warrantyType = type; }
void WarrantyItem::setProvider(const std::string& prov) { provider = prov; }
void WarrantyItem::setWarrantyPrice(double price) { warrantyPrice = price; }
void WarrantyItem::setWarrantyDuration(int duration) { warrantyDuration = duration; }
void WarrantyItem::setWarrantyDurationPeriod(const std::string& period) { warrantyDurationPeriod = period; }