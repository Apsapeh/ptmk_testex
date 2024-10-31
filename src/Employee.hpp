#pragma once

#include <string>
#include <cstdint>

class Employee
{
    std::string fullName;
    std::string birthDate;
    std::string sex;

public:
    Employee(std::string fullName, std::string birthDate, std::string sex);
    
    uint8_t getAge() const;
};