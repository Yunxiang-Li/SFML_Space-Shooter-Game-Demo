#ifndef UTILITY_HPP
#define UTILITY_HPP

// Include standard library C++ libraries.
#include <sstream>

// Forward declaration of sf::Sprite class and sf::Text class.
namespace sf
{
class Sprite;
class Text;
}

// Since std::to_string doesn't work on MinGW we have to implement
// our own to support all platforms.
template <typename T>
std::string toString(const T& value);

// Set sprite's origin to be its center position.
void centerOrigin(sf::Sprite& sprite);
// Set text's origin to be its center position.
void centerOrigin(sf::Text& text);

#include "Utility.inl"
#endif // UTILITY_HPP