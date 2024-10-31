#pragma once

#include "ModeInterface.hpp"

#include <iostream>

class Mode_1 : public ModeInterface {
public:
    virtual void execute(std::vector<std::string> args) override {
        std::cout << "Mode_1" << std::endl;
    }
};
