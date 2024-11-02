#include "DBManager.hpp"
#include <iostream>
#include <string>
#include <string_view>

// Небольшой хак для уменьшения boilerplate кода
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


DBManager::DBManager(std::string url) : conn(url), tx(conn) {
}

DBManager::~DBManager() {
    tx.commit();
    conn.close();
}

void DBManager::addEmployees(std::vector<Employee>* employees) {
    pqxx::stream_to stream =
            pqxx::stream_to::table(tx, {"employees"}, {"fullname", "birthdate", "sex"});

    for (auto const& employee: *employees)
        stream.write_values(employee.getFullName(), employee.getBirthDate(), employee.getSex());
    stream.complete();
}


/*============> Статические методы для удобства работы с БД <==========*/
// Пересоздание таблицы с сотрудниками
void DBManager::createTable(std::string url) {
    DB_CONNECTION_HEADER(tx)

    tx.exec0("DROP TABLE IF EXISTS employees");
    tx.exec0("DROP TYPE IF EXISTS sex_enum;");

    tx.exec0("CREATE TYPE sex_enum AS ENUM ('Male', 'Female');");
    tx.exec0("CREATE TABLE employees "
             "(id SERIAL PRIMARY KEY, fullname TEXT, birthdate DATE, sex sex_enum);");
    tx.exec0("CREATE INDEX ON employees (sex, fullname);");

    DB_CONNECTION_FOOTER(tx)
}

// Добавление сотрудника в БД
void DBManager::addEmployee(std::string url, Employee employee) {
    DB_CONNECTION_HEADER(tx)

    tx.exec_params0(
            "INSERT INTO employees (fullname, birthdate, sex) VALUES ($1, $2, $3)",
            employee.getFullName(), employee.getBirthDate(), employee.getSex()
    );

    DB_CONNECTION_FOOTER(tx)
}

// Получение сотрудников с уникальными фамилией и датой рождения, отсортированных по фамилии
std::vector<Employee> DBManager::getUniqueSortedEmployees(std::string url) {
    DB_CONNECTION_HEADER(tx)

    const char* sql = "SELECT DISTINCT ON (fullname, birthdate) * FROM employees ORDER BY fullname";

    std::vector<Employee> employees;
    for (const auto& row: tx.exec(sql)) {
        Employee employee(row[1].c_str(), row[2].c_str(), row[3].c_str());
        employees.push_back(employee);
    }

    return employees;

    DB_CONNECTION_FOOTER(tx)
}

// Получение сотрудников мужчин с фамилией, начинающимися на F
std::vector<Employee> DBManager::getMaleEmployesWithSurnameStartingWithF(std::string url) {
    DB_CONNECTION_HEADER(tx)

    const char* sql = "SELECT * FROM employees WHERE sex = 'Male' AND fullname LIKE 'F%';";

    std::vector<Employee> employees;
    for (const auto& row: tx.exec(sql)) {
        Employee employee(row[1].c_str(), row[2].c_str(), row[3].c_str());
        employees.push_back(employee);
    }

    return employees;

    DB_CONNECTION_FOOTER(tx)
}
