#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <memory>

#include <pqxx/pqxx>

#include "Modes/ModeInterface.hpp"
#include "Modes/Mode_1.hpp"
#include "Modes/Mode_2.hpp"
#include "Modes/Mode_3.hpp"
#include "Modes/Mode_4.hpp"
#include "Modes/Mode_5.hpp"


int main(int argc, char* argv[]) {
    if (argc < 2) {
        std::cerr << "Usage: " << argv[0] << " <mode>\n";
        return 1;
    }

    std::vector<std::string> args(argv + 1, argv + argc);
    
    std::unordered_map<std::string, std::unique_ptr<ModeInterface>> modes(5);
    modes["1"] = std::make_unique<Mode_1>();
    modes["2"] = std::make_unique<Mode_2>();
    modes["3"] = std::make_unique<Mode_3>();
    modes["4"] = std::make_unique<Mode_4>();
    modes["5"] = std::make_unique<Mode_5>();
    
    if (modes.contains(args[0])) {
        modes[args[0]]->execute(args);
    } else {
        std::cerr << "Unknown mode: " << args[0] << '\n';
        return 1;
    }

    /*for (auto const& arg: args) {
        std::cout << "Argument: " << arg << '\n';
    }*/

    try {
        // Connect to the database.  You can have multiple connections open
        // at the same time, even to the same database.
        pqxx::connection c("postgresql://ghost@localhost/ptmk_testex");
        std::cout << "Connected to " << c.dbname() << '\n';

        // Start a transaction.  A connection can only have one transaction
        // open at the same time, but after you finish a transaction, you
        // can start a new one on the same connection.
        pqxx::work tx(c);

        // Query data of two columns, converting them to std::string and
        // int respectively.  Iterate the rows.
        /*for (auto [name, salary] : tx.query<std::string, int>(
            "SELECT name, salary FROM employee ORDER BY name"))
        {
            std::cout << name << " earns " << salary << ".\n";
        }

        // For large amounts of data, "streaming" the results is more
        // efficient.  It does not work for all types of queries though.
        //
        // You can read fields as std::string_view here, which is not
        // something you can do in most places.  A string_view becomes
        // meaningless when the underlying string ceases to exist.  In this
        // one situation, you can convert a field to string_view and it
        // will be valid for just that one iteration of the loop.  The next
        // iteration may overwrite or deallocate its buffer space.
        for (auto [name, salary] : tx.stream<std::string_view, int>(
            "SELECT name, salary FROM employee"))
        {
            std::cout << name << " earns " << salary << ".\n";
        }

        // Execute a statement, and check that it returns 0 rows of data.
        // This will throw pqxx::unexpected_rows if the query returns rows.
        std::cout << "Doubling all employees' salaries...\n";
        tx.exec0("UPDATE employee SET salary = salary*2");

        // Shorthand: conveniently query a single value from the database.
        int my_salary = tx.query_value<int>(
            "SELECT salary FROM employee WHERE name = 'Me'");
        std::cout << "I now earn " << my_salary << ".\n";

        // Or, query one whole row.  This function will throw an exception
        // unless the result contains exactly 1 row.
        auto [top_name, top_salary] = tx.query1<std::string, int>(
            R"(
                SELECT name, salary
                FROM employee
                WHERE salary = max(salary)
                LIMIT 1
            )");
        std::cout << "Top earner is " << top_name << " with a salary of "
                  << top_salary << ".\n";

        // If you need to access the result metadata, not just the actual
        // field values, use the "exec" functions.  Most of them return
        // pqxx::result objects.
        pqxx::result res = tx.exec("SELECT * FROM employee");
        std::cout << "Columns:\n";
        for (pqxx::row_size_type col = 0; col < res.columns(); ++col)
            std::cout << res.column_name(col) << '\n';

        // Commit the transaction.  If you don't do this, the database will
        // undo any changes you made in the transaction.
        std::cout << "Making changes definite: ";
        tx.commit();
        std::cout << "OK.\n";*/

        tx.exec_params0("INSERT INTO test (name) VALUES ($1)", pqxx::params{"Timofey Kirichenko"});
        tx.commit();
        std::cout << "OK.\n";
    } catch (std::exception const& e) {
        std::cerr << "ERROR: " << e.what() << '\n';
        return 1;
    }
    return 0;
}
