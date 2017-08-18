// --------------------------------------------------------------------------
#pragma once
// --------------------------------------------------------------------------
// Simple wrapper class for sqlite3 functions.
// internal sqlite3 pointer is always valid; class can throw an exception
// during construction if sqlite couldn't create a new db file! ~ JSt
// --------------------------------------------------------------------------
#include <string>
#include <exception>
#include <optional>
#include <vector>

// typedefs
using sql_error = std::optional<std::string>;
using sql_row   = std::vector<std::string>;
using sql_rows  = std::vector<sql_row>;

// container for sql 'answers'
struct [[nodiscard]] sql_result {
    sql_rows rows;
    sql_error error;
};

// thrown if the creation/open of a db failed
class db_creation_error : public std::exception {
public:
    explicit db_creation_error() {/*empty!*/}
};


// forward decls.
struct sqlite3;


class [[nodiscard]] sql_wrapper {
public:

    // create or open a sqlite-db
    // throws 'db_creation_error' if neither is possible
    sql_wrapper(const std::string& db_name);

    // close db
    ~sql_wrapper();

    sql_wrapper(sql_wrapper&&)     = default; // allow move semantics
    sql_wrapper(const sql_wrapper&) = delete; // don't allow copying

    // send sql commands to the connected db
    // can be used for SELECT, DROP, COUNT ... etc.
    sql_result execute_cmd(const std::string& cmd) const;

    std::string db_name() const;

private:
    sqlite3* db_;
    char* error_msg_;
    const std::string name_;
};
