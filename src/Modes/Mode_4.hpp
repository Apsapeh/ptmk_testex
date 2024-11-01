#pragma once

#include "ModeInterface.hpp"
#include "../DBManager.hpp"

#include <random>
#include <iostream>

// Генерация имени
inline static std::string generateName(
        std::mt19937* generator, std::uniform_int_distribution<>* upper,
        std::uniform_int_distribution<>* lower
);
// Генерация даты рождения
inline static std::string generadeBirthDate(
        std::mt19937* generator, std::uniform_int_distribution<>* year,
        std::uniform_int_distribution<>* month, std::uniform_int_distribution<>* day
);


class Mode_4 : public ModeInterface {
public:
    virtual void execute(std::vector<std::string> args, std::string db_url) override {
        DBManager db(db_url);

        // Генератор случайных чисел.
        std::random_device random_device;
        std::mt19937 generator(random_device());
        generator.seed(10045174); // Для детерминированности

        // Распределитель случайных чисел в диапазоне.
        std::uniform_int_distribution<> upper('A', 'Z'); // Заглавные
        std::uniform_int_distribution<> lower('a', 'z'); // Прописные

        std::uniform_int_distribution<> year(1960, 2006);
        std::uniform_int_distribution<> month(101, 112);
        std::uniform_int_distribution<> day(101, 128);
        // +100, чтоб строка после обрезания была 01, 02..., а не 1, 2...

        std::uniform_int_distribution<> sex(0, 1); // 0 - мужчина, 1 - женщина

        // Генерация 1_000_000 сотрудников, пакетами по 100_000.
        const int PACK_COUNT = 10;
        const int PACK_SIZE = 100000;
        for (int i = 0; i < PACK_COUNT; i++) {
            std::vector<Employee> employees;
            employees.reserve(PACK_SIZE);
            for (int i = 0; i < PACK_SIZE; i++) {
                std::string fullname = generateName(&generator, &upper, &lower);
                std::string date = generadeBirthDate(&generator, &year, &month, &day);
                std::string str_sex = sex(generator) == 0 ? "Male" : "Female";

                Employee employee(fullname, date, str_sex);
                employees.push_back(employee);
            }

            db.addEmployees(&employees);
            std::cout << std::fixed << std::setprecision(1)
                      << float(i + 1) / float(PACK_COUNT) * 100 << "%" << std::endl;
        }

        // Генерация 100 сотрудников мужчин, с фамилией на F
        std::vector<Employee> employees;
        employees.reserve(100);
        for (int i = 0; i < 100; i++) {
            std::string fullname = generateName(&generator, &upper, &lower);
            std::string date = generadeBirthDate(&generator, &year, &month, &day);

            fullname[0] = 'F';

            Employee employee(fullname, date, "Male");
            employees.push_back(employee);
        }

        db.addEmployees(&employees);
        std::cout << "Done!" << std::endl;
    }
};


// Генерация имени
inline static std::string generateName(
        std::mt19937* generator, std::uniform_int_distribution<>* upper,
        std::uniform_int_distribution<>* lower
) {
    // clang-format off
    const char surname[] = {
        (char)(*upper)(*generator),
        (char)(*lower)(*generator),
        (char)(*lower)(*generator),
    };

    const char name[] = {
        (char)(*upper)(*generator),
        (char)(*lower)(*generator),
    };

    const char fathers_name[] = {
        (char)(*upper)(*generator),
        (char)(*lower)(*generator),
    };
    // clang-format on

    std::string fullname;
    fullname.reserve(9);
    fullname.append((const char*) &surname, 3)
            .append(1, ' ')
            .append((const char*) &name, 2)
            .append(1, ' ')
            .append((const char*) &fathers_name, 2);
    return fullname;
}

// Генерация даты рождения
inline static std::string generadeBirthDate(
        std::mt19937* generator, std::uniform_int_distribution<>* year,
        std::uniform_int_distribution<>* month, std::uniform_int_distribution<>* day
) {
    std::string birth_date;
    birth_date.reserve(10);
    birth_date.append(std::to_string((*year)(*generator)))
            .append("-")
            .append(std::to_string((*month)(*generator)).substr(1, 2))
            .append("-")
            .append(std::to_string((*day)(*generator)).substr(1, 2));

    return birth_date;
}
