// ---------------------------------------------------------------------------------------
#pragma once
// ---------------------------------------------------------------------------------------
// Free-standing functions that help with printing/formatting every kind of value ~ JSt
// ---------------------------------------------------------------------------------------
#include <variant>
using Arg = std::variant<int, double, std::string>;
const size_t int_index = 0;
const size_t double_index = 1;
const size_t string_index = 2;


// --------------------------------------------------------------------------------
// turn members of the Arg variant into strings. There is a nicer version with
// 'if constexpr(std::is_same_v<T,...>) possible, but wasn't available during
// the implementation of this function! ~ JSt
// --------------------------------------------------------------------------------
std::string to_string(const Arg& arg);

// --------------------------------------------------------------------------------
// helps to create a string combined with different native datatypes. Works similar
// to print() functions and replaces formating with std::stringstream.
// Inspired by https://github.com/fmtlib/fmt and Andrei Alexandrescus 'safe_print'
// function ~ JSt
//
// example: auto text = format("%0, %1, %2 are %3", 0, 1, 2.0, "NUMBERS");
// -> text = "0, 1, 2.000000 are NUMBERS"
// --------------------------------------------------------------------------------
std::string format(const char* fmt, const Arg* values, size_t values_size);

// --------------------------------------------------------------------------------
// variadic overload of 'format'. creates an array of variants that is easier to
// handle then raw values ~ JSt
// --------------------------------------------------------------------------------
template < class ... Args >
std::string format(const char* fmt, const Args& ... values)
// --------------------------------------------------------------------------------
{
    Arg values_as_array[] = { values... };
    return format(fmt, values_as_array, sizeof ... (Args));
}