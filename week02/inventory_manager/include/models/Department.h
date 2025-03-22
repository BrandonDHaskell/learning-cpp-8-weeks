#ifndef DEPARTMENT_H
#define DEPARTMENT_H

#include <string>

class Department {
private:
    int departmentID;
    std::string name;

public:
    Department();
    Department(int id, const std::string& name);

    // Getters
    int getDepartmentID() const;
    std::string getName() const;

    // Setters
    void setDepartmentID(int id);
    void setName(const std::string& name);
};

#endif // DEPARTMENT_H