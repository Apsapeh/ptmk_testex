#pragma once

#include "ModeInterface.hpp"

#include <iostream>
#include "../DBManager.hpp"

class Mode_1 : public ModeInterface {
public:
    virtual void execute(std::vector<std::string> args, std::string db_url) override {
        DBManager::createTable(std::move(db_url));
        std::cout << "Table created" << std::endl;
    }
};
