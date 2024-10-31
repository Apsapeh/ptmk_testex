#pragma once

#include "ModeInterface.hpp"

#include "../DBManager.hpp"

#include <iostream>

class Mode_3 : public ModeInterface {
public:
    virtual void execute(std::vector<std::string> args, std::string db_url) override {
        std::vector<Employee> employees = DBManager::getUniqueSortedEmployees(std::move(db_url));

        for (const auto& employee: employees) {
            std::cout << employee.getFullName() << " - " << employee.getBirthDate() << " - "
                      << employee.getSex() << " - " << (int)employee.getAge() << std::endl;
        }
    }
};
