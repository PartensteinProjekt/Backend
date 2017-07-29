// ----------------------------------------------------------------------------------------------------------------------
#include <format.h>
// ----------------------------------------------------------------------------------------------------------------------
#include <string>
using std::string;
using std::to_string;

// --------------------------------------------------------------------------------
string to_string(const Arg& arg)
// --------------------------------------------------------------------------------
{
    auto index = arg.index();
    if (index == 0) {
        return to_string(std::get<int_index>(arg));
    }
    if (index == 1) {
        return to_string(std::get<double_index>(arg));
    }
    return std::get<string_index>(arg);
}

// --------------------------------------------------------------------------------
string format(const char* fmt, const Arg* values, size_t values_size)
// --------------------------------------------------------------------------------
{
    string out;
    while (*fmt) {
        if (*fmt == '%') {
            fmt++;
            int index = std::atoi(fmt);
            if (index > values_size) {
                throw std::runtime_error("bad index!");
            }

            out += to_string(values[index]);
            while (*fmt) {
                fmt++;
                if (*fmt == ' ') {
                    break;
                }
            }
        }
        else {
            out += *fmt;
            fmt++;
        }
    }
    return out;
}
