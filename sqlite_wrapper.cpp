// ------------------------------------------------------------------------------------------
#include "sqlite_wrapper.h"
// ------------------------------------------------------------------------------------------
#include <sqlite3.h> // sqlite3_open, sqlite3_close, sqlite3_exec
#include <iso646.h>  // alternative operators


// ------------------------------------------------------------------------------------------
// sqlite3_exec needs a callback function to read data from querys
// ------------------------------------------------------------------------------------------
int callback(void *not_used, int argc, char **argv, char **col_name)
// ------------------------------------------------------------------------------------------
{
    return 0;
}

// ------------------------------------------------------------------------------------------
sql_wrapper::sql_wrapper(const std::string& name) : db_{nullptr}, name_{name}, error_msg_{0}
// ------------------------------------------------------------------------------------------
{
    auto result = sqlite3_open(name.c_str(), &db_);
    if (db_ == nullptr or result != SQLITE_OK) {
        throw db_creation_error{};
    }
}

// ------------------------------------------------------------------------------------------
sql_wrapper::~sql_wrapper()
// ------------------------------------------------------------------------------------------
{
    sqlite3_close(db_);
}

// ------------------------------------------------------------------------------------------
sql_error sql_wrapper::execute_cmd(const std::string& cmd) const
// ------------------------------------------------------------------------------------------
{
    char* error_msg = {};
    auto result = sqlite3_exec(db_, cmd.c_str(), callback, 0, &error_msg);
    if (result == SQLITE_OK) {
        return {};
    }
    return { error_msg };
}
