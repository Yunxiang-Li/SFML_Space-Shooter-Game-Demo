#ifndef STRINGHELPERS_HPP
#define STRINGHELPERS_HPP

// Include standard library C++ libraries.
#include <sstream>

// Since std::to_string doesn't work on MinGW we have to implement our own to support all platforms.
template <typename T>
std::string toString(const T& value);

//Create an .inl file and #include it at the end of header file. This is equivalent to putting the
//function definition at the end of the header file, but this lets us keep declaration and definition separate.
#include <StringHelpers.inl>
#endif // STRINGHELPERS_HPP