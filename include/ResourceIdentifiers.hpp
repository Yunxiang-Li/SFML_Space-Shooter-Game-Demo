#ifndef RESOURCEIDENTIFIERS_HPP
#define RESOURCEIDENTIFIERS_HPP

// Forward declaration of SFML classes to avoid #include.
namespace sf
{
  class Texture;
  class Font;
}

// Create a namespace called Textures to hold all sf::Texture objects we need for the game by enum.
namespace Textures
{
  // enum name is ID.
  enum ID
    {
      Eagle,
      Raptor,
      Desert,
      TitleScreen,
    };
}

// Create a namespace called Fonts to hold all sf::Font objects we need for the game by enum.
namespace Fonts
{
  // enum name is also ID.
  enum ID
  {
    Main,
  };
}

// Forward declaration and a few type definitions
template <typename Resource, typename Identifier>
class ResourceHolder;

// We use TextureHolder to be an alias of ResourceHolder<sf::Texture, Textures::ID> type.
typedef ResourceHolder<sf::Texture, Textures::ID>   TextureHolder;

// We use FontHolder to be an alias of ResourceHolder<sf::Font, Fonts::ID> type.
typedef ResourceHolder<sf::Font, Fonts::ID>			FontHolder;

#endif // RESOURCEIDENTIFIERS_HPP