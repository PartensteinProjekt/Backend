#include <sql.h>

#include <sqlite_wrapper.h>

using std::string;
using std::unique_ptr;
using std::make_unique;
using std::initializer_list;
using std::ostream;
using std::vector;

#include <algorithm>
using std::replace;

#include <fstream>
using std::ifstream;
using std::getline;

// ----------------------------------------------------------------------------------------------------------------------
unique_ptr<sql_wrapper> sql::create_database(const string& db_name, initializer_list<string> table_names, ostream& os)
// ----------------------------------------------------------------------------------------------------------------------
{
    auto db = make_unique<sql_wrapper>(db_name);

    for (auto name : table_names) {
        auto result = db->execute_cmd(sql::file_to_string(name));
        if (result.error) {
            os << "ERROR: " << result.error.value() << '\n';
            throw std::runtime_error("bad query during 'create_db'");
        }
    }

    return std::move(db);
}

// ----------------------------------------------------------------------------------------------------------------------
string sql::file_to_string(const string& sql_file_name)
// ----------------------------------------------------------------------------------------------------------------------
{
    string line = {};
    ifstream sql_file_stream;
    string sql_text = {};
    sql_file_stream.open(sql_file_name, std::ios::binary);
    while (getline(sql_file_stream, line)) {
        sql_text += line;
    }
    replace(std::begin(sql_text), std::end(sql_text), '\t', ' ');
    replace(std::begin(sql_text), std::end(sql_text), '\r', ' ');
    return sql_text;
}

// ----------------------------------------------------------------------------------------------------------------------
vector<string> sql::table_names(const sql_wrapper* db)
// ----------------------------------------------------------------------------------------------------------------------
{
    auto result = db->execute_cmd("SELECT name FROM sqlite_master WHERE type='table' ORDER BY name;");
    if (result.error) {
        // LOGGING!
        return {};
    }

    vector<string> names{};
    for (auto row : result.rows) {
        names.push_back(row.front());
    }
    return names;
}