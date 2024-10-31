#pragma once

#include "ModeInterface.hpp"

#include <iostream>

class Mode_4 : public ModeInterface {
public:
    virtual void execute(std::vector<std::string> args, std::string db_url) override {
        std::cout << "Mode_2" << std::endl;
    }
};
