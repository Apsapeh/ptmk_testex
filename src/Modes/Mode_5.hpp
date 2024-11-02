#pragma once

#include "ModeInterface.hpp"
#include "../DBManager.hpp"

#include <iostream>

class Mode_5 : public ModeInterface {
public:
    virtual void execute(std::vector<std::string> args, std::string db_url) override {
        const auto t0 = std::chrono::high_resolution_clock::now();
        std::vector<Employee> employees =
                DBManager::getMaleEmployesWithSurnameStartingWithF(std::move(db_url));
        const auto t1 = std::chrono::high_resolution_clock::now();

        if (args.size() > 1 and args[1] == "-s")
            goto skip_print;

        for (const auto& employee: employees)
            std::cout << employee.toString() << "\n";
    skip_print:

        std::cout << "Elapsed time: "
                  << std::chrono::duration_cast<std::chrono::milliseconds>(t1 - t0).count() << " ms"
                  << std::endl;
    }
};
