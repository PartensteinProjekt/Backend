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
using sql_error = std::optional<std::string>;


// thrown if the creation/open of a db failed
class db_creation_error : public std::exception {
public:
    explicit db_creation_error() {/*empty!*/}
};


// forward decls.
struct sqlite3;


class sql_wrapper {
public:

    sql_wrapper(const std::string& name);
    ~sql_wrapper();

    sql_error execute_cmd(const std::string& cmd) const;

private:
    sqlite3* db_;
    char* error_msg_;
    const std::string name_;
};
