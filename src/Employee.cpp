#include "Employee.hpp"
#include "DBManager.hpp"
#include <iostream>
#include <ctime>

Employee::Employee(std::string fullName, std::string birthDate, std::string sex) {
    this->fullName = fullName;
    this->birthDate = birthDate;
    this->sex = sex;
}

uint8_t Employee::getAge() const {
    // Получаем текущее время
    std::time_t t = std::time(nullptr);
    std::tm now = *std::localtime(&t); // Преобразуем в локальное время

    // Извлекаем год, месяц и день
    int year = now.tm_year + 1900; // tm_year хранит годы, начиная с 1900
    int month = now.tm_mon + 1; // tm_mon хранит месяцы, начиная с 0 (январь)
    int day = now.tm_mday;

    // Извлекаем год, месяц и день даты рождения YYYY-MM-DD
    int birthYear = std::stoi(this->birthDate.substr(0, 4));
    int birthMonth = std::stoi(this->birthDate.substr(5, 2));
    int birthDay = std::stoi(this->birthDate.substr(8, 2));

    int age = year - birthYear;
    // Если текущий день и месяц меньше дня и месяца рождения, то уменьшаем возраст
    if (month < birthMonth || (month == birthMonth && day < birthDay))
        age--;

    return age;
}

void Employee::addToDB(std::string db_url) const {
    DBManager::addEmployee(std::move(db_url), *this);
}

std::string Employee::getFullName() const {
    return this->fullName;
}

std::string Employee::getBirthDate() const {
    return this->birthDate;
}

std::string Employee::getSex() const {
    return this->sex;
}
