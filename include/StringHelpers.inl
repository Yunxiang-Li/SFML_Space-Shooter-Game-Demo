// Include standard library C++ libraries.
#include <iostream>
#include <sstream>

/**
 * Definitions of function toString templates.
 */
template <typename T>
std::string toString(const T& value)
{
  std::stringstream stream;
  stream << value;
  return stream.str();
}