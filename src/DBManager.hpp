#pragma once

#include "Employee.hpp"
#include <pqxx/pqxx>

class DBManager {
    pqxx::connection conn;
    pqxx::work tx;

public:
    DBManager(std::string url);
    ~DBManager();
    void addEmployees(std::vector<Employee>* employees);

    // Статические методы для удобства работы с БД
    static void createTable(std::string url);
    static void addEmployee(std::string url, Employee employee);
    static std::vector<Employee> getUniqueSortedEmployees(std::string url);
    static std::vector<Employee> getMaleEmployesWithSurnameStartingWithF(std::string url);
};
