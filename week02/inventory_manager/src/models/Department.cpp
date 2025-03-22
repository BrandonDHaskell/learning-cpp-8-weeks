#include "models/Department.h"

Department::Department() : departmentID(0), name("") {}

Department::Department(int id, const std::string& name) : departmentID(id), name(name) {}

int Department::getDepartmentID() const { return departmentID; }
std::string Department::getName() const { return name; }

void Department::setDepartmentID(int id) { departmentID = id; }
void Department::setName(const std::string& n) { name = n; }