#pragma once

#include "Employee.hpp"

#include <pqxx/pqxx>

class DBManager {
    pqxx::connection conn;

public:
    DBManager(std::string url);
    static void createTable(std::string url);
    static void addEmployee(std::string url, Employee employee);
    static std::vector<Employee> getUniqueSortedEmployees(std::string url);
};
