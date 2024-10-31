#include "DBManager.hpp"
#include <iostream>

#define DB_CONNECTION_HEADER(var)                                                                  \
    try {                                                                                          \
        pqxx::connection c(url);                                                                   \
        pqxx::work var(c);

#define DB_CONNECTION_FOOTER(var)                                                                  \
    var.commit();                                                                                  \
    }                                                                                              \
    catch (std::exception const& e) {                                                              \
        std::cerr << e.what() << '\n';                                                             \
        exit(1);                                                                                   \
    }

DBManager::DBManager(std::string url) {
    conn = pqxx::connection(url);
}

void DBManager::createTable(std::string url) {
    DB_CONNECTION_HEADER(tx)

    tx.exec0("DROP TABLE IF EXISTS employees");
    tx.exec0("CREATE TABLE employees (id SERIAL PRIMARY KEY, fullname TEXT, birthdate DATE, sex "
             "TEXT)");

    DB_CONNECTION_FOOTER(tx)
}

void DBManager::addEmployee(std::string url, Employee employee) {
    DB_CONNECTION_HEADER(tx)

    tx.exec_params0(
            "INSERT INTO employees (fullname, birthdate, sex) VALUES ($1, $2, $3)",
            employee.getFullName(), employee.getBirthDate(), employee.getSex()
    );

    DB_CONNECTION_FOOTER(tx)
}

std::vector<Employee> DBManager::getUniqueSortedEmployees(std::string url) {
    DB_CONNECTION_HEADER(tx)

    std::vector<Employee> employees;

    const char* sql = "SELECT DISTINCT ON (fullname, birthdate) * FROM employees ORDER BY fullname";

    for (const auto& row: tx.exec(sql)) {
        Employee employee(row[1].c_str(), row[2].c_str(), row[3].c_str());
        employees.push_back(employee);
    }

    return employees;

    DB_CONNECTION_FOOTER(tx)
}
