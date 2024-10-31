#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <memory>

#include <pqxx/pqxx>

#include "DBManager.hpp"
#include "Employee.hpp"
#include "Modes/ModeInterface.hpp"
#include "Modes/Mode_1.hpp"
#include "Modes/Mode_2.hpp"
#include "Modes/Mode_3.hpp"
#include "Modes/Mode_4.hpp"
#include "Modes/Mode_5.hpp"


// URL подключения к базе данных
const std::string DB_URL = "postgresql://ghost@localhost/ptmk_testex";


int main(int argc, char* argv[]) {
    if (argc < 2) {
        std::cerr << "Usage: " << argv[0] << " <mode>\n";
        return 1;
    }

    // Преобразование аргументов командной строки в вектор строк
    std::vector<std::string> args(argv, argv + argc);
    std::string mode = args[1];
    args.erase(args.begin() + 1); // Удаление режима из вектора аргументов

    // Создание объектов режимов
    std::unordered_map<std::string, std::unique_ptr<ModeInterface>> modes(5);
    modes["1"] = std::make_unique<Mode_1>();
    modes["2"] = std::make_unique<Mode_2>();
    modes["3"] = std::make_unique<Mode_3>();
    modes["4"] = std::make_unique<Mode_4>();
    modes["5"] = std::make_unique<Mode_5>();

    // Запуск программы в соответствии с выбранным режимом
    if (modes.contains(mode)) {
        modes[mode]->execute(std::move(args), DB_URL);
    } else {
        std::cerr << "Unknown mode: " << mode << '\n';
        return 1;
    }
}
