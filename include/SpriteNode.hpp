#ifndef SPRITENODE_HPP
#define SPRITENODE_HPP

// Include project header files
#include "SceneNode.hpp"

// Include our Third-Party SFML header
#include <SFML/Graphics/Sprite.hpp>

/**
 * This class represents a sprite manipulation object to manipulate
 * with a sf::Sprite object which inherits from SceneNode class.
 */
class SpriteNode : public SceneNode
{
 public:
  // Two constructors.
  explicit			SpriteNode(const sf::Texture& texture);
  SpriteNode(const sf::Texture& texture, const sf::IntRect& textureRect);

 private:
  // Draw the current SpriteNode object's sprite.
  virtual void		drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const override;

 private:
  // Sprite member of the current SpriteNode object.
  sf::Sprite			mSprite;
};

#endif // SPRITENODE_HPP