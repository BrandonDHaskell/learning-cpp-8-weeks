#ifndef IPERISHABLE_H
#define IPERISHABLE_H

#include <string>

class IPerishable {
public:
    virtual ~IPerishable() = default;

    // Getters
    virtual std::string getLotNumber() const = 0;
    virtual std::string getExpirationDate() const = 0;
    virtual double getStorageTempMinCelsius() const = 0;
    virtual double getStorageTempMaxCelsius() const = 0;

    // Setters
    virtual void setLotNumber(const std::string& lot) = 0;
    virtual void setExpirationDate(const std::string& date) = 0;
    virtual void setStorageTempMinCelsius(double temp) = 0;
    virtual void setStorageTempMaxCelsius(double temp) = 0;
};

#endif // IPERISHABLE_H