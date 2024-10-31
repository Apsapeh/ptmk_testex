#pragma once

#include <vector>
#include <string>

// Абстрактный класс режима работы программы
class ModeInterface {
public:
    virtual ~ModeInterface() = default;
    virtual void execute(std::vector<std::string> args) = 0;
};
