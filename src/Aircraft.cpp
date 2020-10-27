// Project header files
#include "Aircraft.hpp"
#include "ResourceHolder.hpp"
#include "Category.hpp"

// Include our Third-Party SFML header
#include <SFML/Graphics/RenderTarget.hpp>


/**
 * A isolate method that maps the aircraft type to the corresponding texture ID.
 * @param type A Aircraft::Type enum indicates the type name of Aircraft object we want.
 * @return A Textures::ID enum indicates the specific Textures id we need.
 */
Textures::ID toTextureID(Aircraft::Type type)
{
  switch (type)
  {
    case Aircraft::Eagle:
      return Textures::Eagle;

    case Aircraft::Raptor:
      return Textures::Raptor;
  }
  return Textures::Eagle;
}

/**
 * Constructor of the Aircraft class which using a Type(enum) and a const TextureHolder object.
 * @param type a enum indicates which texture we want to construct with.
 * @param textures a ResourceHolder<sf::Texture, Textures::ID> object which hold all sf::Texture objects and their IDs.
 */
Aircraft::Aircraft(Type type, const TextureHolder& textures)
    : mType(type)
    , mSprite(textures.get(toTextureID(type)))
{
  // Get the local bounding rectangle of the Aircraft object.
  // The rectangle is of type sf::FloatRect, which stores four float variables called left, top, width, and height.
  sf::FloatRect bounds = mSprite.getLocalBounds();
  // Set the local origin of the object to be its center.
  mSprite.setOrigin(bounds.width / 2.f, bounds.height / 2.f);
}

/**
 * Override drawCurrent method from SceneNode class to draw the current Aircraft object.
 * @param target indicates the sf::RenderTarget object we want to draw to
 * @param states indicates the current object's parent object's sf::RenderStates(altogether four states, the blend mode
 * , the transform, the texture, the shader) of the parent node.
 */
void Aircraft::drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const
{
  // Draw Aircraft object's sprite.
  target.draw(mSprite, states);
}

/**
 * Returns the category of the game object.
 * @return an unsigned int indicates the category of the game object.
 */
unsigned int Aircraft::getCategory() const
{
  // Check which type the Aircraft is.
  switch (mType)
  {
    case Eagle:
      return Category::PlayerAircraft;

    default:
      return Category::EnemyAircraft;
  }
}
