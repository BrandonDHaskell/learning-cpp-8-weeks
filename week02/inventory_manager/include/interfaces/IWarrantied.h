#ifndef IWARRANTIED_H
#define IWARRANTIED_H

#include <string>

class IWarrantied {
public:
    virtual ~IWarrantied() = default;

    // Getters
    virtual std::string getSerialNumber() const = 0;
    virtual std::string getWarrantyType() const = 0;
    virtual std::string getProvider() const = 0;
    virtual double getWarrantyPrice() const = 0;
    virtual int getWarrantyDuration() const = 0;
    virtual std::string getWarrantyDurationPeriod() const = 0;

    // Setters
    virtual void setSerialNumber(const std::string& serial) = 0;
    virtual void setWarrantyType(const std::string& type) = 0;
    virtual void setProvider(const std::string& provider) = 0;
    virtual void setWarrantyPrice(double price) = 0;
    virtual void setWarrantyDuration(int duration) = 0;
    virtual void setWarrantyDurationPeriod(const std::string& period) = 0;
};

#endif // IWARRANTIED_H