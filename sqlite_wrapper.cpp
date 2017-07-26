// ------------------------------------------------------------------------------------------
#include "sqlite_wrapper.h"
// ------------------------------------------------------------------------------------------
#include <sqlite3.h> // sqlite3_open, sqlite3_close, sqlite3_exec
#include <iso646.h>  // alternative operators

#include <iostream>

// ------------------------------------------------------------------------------------------
// sqlite3_exec needs a callback function to read data from querys
// ------------------------------------------------------------------------------------------
int callback(void* data, int argc, char **argv, char **col_name)
// ------------------------------------------------------------------------------------------
{
    // no data container given, return without doing anything
    if (data == nullptr) {
        return SQLITE_OK;
    }

    // cast that void* to something usefull and fill it with data
    // try&catch for possible pointer-hocuspocus-exceptions... don't handle further,
    // just report an error back! ~ JSt
    try {
        sql_result * query = static_cast<sql_result*>(data);
        query->rows.emplace_back(argv, argv + argc);
    }
    catch (...) {
        return SQLITE_ERROR;
    }
    return SQLITE_OK;
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
sql_result sql_wrapper::execute_cmd(const std::string & select_cmd) const
// ------------------------------------------------------------------------------------------
{
    sql_result query = {};

    char* error_msg = {};
    auto result = sqlite3_exec(db_, select_cmd.c_str(), callback, &query, &error_msg);
    if (result == SQLITE_OK) {
        return query;
    }
    return { {}, error_msg };
}
