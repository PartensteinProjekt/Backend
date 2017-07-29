// ----------------------------------------------------------------------------------------------------------------------
#pragma once
// ----------------------------------------------------------------------------------------------------------------------
// functions to handle a complete db ~ JSt
// ----------------------------------------------------------------------------------------------------------------------
#include <memory>
#include <string>
#include <iostream>
#include <vector>

// forward decl.
class sql_wrapper;

namespace sql {

// ----------------------------------------------------------------------------------------------------------------------
// Create a new db or open an existing db. Uses xxx.sql files to create tables.
// 'create_databse' will always create a valid unique_ptr, or else throw an exception! ~ JSt
// ----------------------------------------------------------------------------------------------------------------------
std::unique_ptr<sql_wrapper> create_database(const std::string& db_name, std::initializer_list<std::string> table_names, std::ostream& os = std::cout);

// ----------------------------------------------------------------------------------------------------------------------
// read .sql files and return the contents as a single string ~ JSt
// ----------------------------------------------------------------------------------------------------------------------
std::string file_to_string(const std::string& sql_file_name);

// ----------------------------------------------------------------------------------------------------------------------
// wrapper for "SELECT name FROM sqlite_master WHERE type='table' ORDER BY name;" ~ JSt
// ----------------------------------------------------------------------------------------------------------------------
std::vector<std::string> table_names(const sql_wrapper* db);

// ----------------------------------------------------------------------------------------------------------------------
// use native c++ functions to copy a db file - the file shouldn't be changed in another thread during copying! ~ JSt
// ----------------------------------------------------------------------------------------------------------------------
std::unique_ptr<sql_wrapper> copy_database(const sql_wrapper* db_to_copy, const std::string& new_name);

}