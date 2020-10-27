#ifndef RESOURCEIDENTIFIERS_HPP
#define RESOURCEIDENTIFIERS_HPP

// Forward declaration of SFML classes to avoid #include.
namespace sf
{
  class Texture;
}

// Create a namespace called Textures to hold all sf::Texture we need for the game by enum.
namespace Textures
{
  // enum name is ID.
  enum ID
    {
      Eagle,
      Raptor,
      Desert,
    };
}

// Forward declaration and a few type definitions
template <typename Resource, typename Identifier>
class ResourceHolder;

// We use TextureHolder to be an alias of ResourceHolder<sf::Texture, Textures::ID> type.
typedef ResourceHolder<sf::Texture, Textures::ID> TextureHolder;

#endif // RESOURCEIDENTIFIERS_HPP