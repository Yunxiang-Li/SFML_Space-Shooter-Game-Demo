#ifndef AIRCRAFT_HPP
#define AIRCRAFT_HPP

// Include project header files
#include "Entity.hpp"
#include "ResourceIdentifiers.hpp"

// Include C++ standard headers.
#include <SFML/Graphics/Sprite.hpp>

/**
 * Aircraft class represents all aircraft in the game which inherits the Entity class.
 */
class Aircraft : public Entity
{
 public:
  // Store all types of aircraft by enum.
  enum Type
  {
    Eagle,
    Raptor,
  };

 public:
  // Constructor of the Aircraft class which using a Type(enum) and a const TextureHolder object.
  explicit  Aircraft(Type type, const TextureHolder& textures);

 private:
  // Override drawCurrent method from SceneNode class to draw the current Aircraft object.
  void		drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const override;

  // Returns the category of the game object.
  unsigned int	getCategory() const override;

 private:
  Type				    mType;
  // Sprite of each Aircraft object to render.
  sf::Sprite			mSprite;
};

#endif // AIRCRAFT_HPP