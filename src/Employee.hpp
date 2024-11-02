#pragma once

#include <string>
#include <cstdint>

// Класс сотрудника
class Employee {
    std::string fullName;
    std::string birthDate;
    std::string sex;

public:
    Employee(std::string fullName, std::string birthDate, std::string sex);

    uint8_t getAge() const;
    void addToDB(std::string db_url) const;

    std::string getFullName() const;
    std::string getBirthDate() const;
    std::string getSex() const;

    std::string toString() const;
};
