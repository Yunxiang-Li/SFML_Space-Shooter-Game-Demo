// Include project header files
#include "Utility.hpp"

// Include our Third-Party SFML header
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Text.hpp>

// Include standard library C++ libraries.
#include <cmath>

/**
 * Set sprite's origin to be its center position.
 * @param sprite a sf::Sprite object
 */
void centerOrigin(sf::Sprite& sprite)
{
  sf::FloatRect bounds = sprite.getLocalBounds();
  sprite.setOrigin(std::floor(bounds.left + bounds.width / 2.f), std::floor(bounds.top + bounds.height / 2.f));
}

/**
 * Set text's origin to be its center position.
 * @param text a sf::Text object.
 */
void centerOrigin(sf::Text& text)
{
  sf::FloatRect bounds = text.getLocalBounds();
  text.setOrigin(std::floor(bounds.left + bounds.width / 2.f), std::floor(bounds.top + bounds.height / 2.f));
}