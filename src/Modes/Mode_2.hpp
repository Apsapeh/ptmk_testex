#pragma once

#include "ModeInterface.hpp"
#include "../Employee.hpp"

#include <string>
#include <iostream>

class Mode_2 : public ModeInterface {
public:
    virtual void execute(std::vector<std::string> args, std::string db_url) override {
        if (args.size() < 4) {
            std::cerr << "Usage: " << args[0] << " <full name> <birtdate> <sex>" << std::endl;
            return;
        }

        // Проверка на соответсвие даты формату YYYY-MM-DD
        if (args[2].size() != 10 || args[2][4] != '-' || args[2][7] != '-') {
            std::cerr << "Invalid birthdate format (YYYY-MM-DD)" << std::endl;
            return;
        }

        // Проверка на валидность пола
        if (args[3] != "Male" && args[3] != "Female") {
            std::cerr << "Sex must be 'Male' or 'Female'" << std::endl;
            return;
        }

        Employee employee(args[1], args[2], args[3]);
        employee.addToDB(std::move(db_url));

        std::cout << "Employee added" << std::endl;
    }
};
