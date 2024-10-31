#pragma once

#include "ModeInterface.hpp"

#include <iostream>

class Mode_3 : public ModeInterface
{
public:
    virtual void execute(std::vector<std::string> args) override {
        std::cout << "Mode_2" << std::endl;
    }
};