// Include project header files
#include "SpriteNode.hpp"

// Include our Third-Party SFML header
#include <SFML/Graphics/RenderTarget.hpp>

/**
 * One constructor of SpriteNode class.
 * @param texture a sf::Texture object indicates the sprite member's texture
 */
SpriteNode::SpriteNode(const sf::Texture& texture)
    : mSprite(texture)
{
}

/**
 * Another constructor of SpriteNode class.
 * @param texture a sf::Texture object indicates the sprite member's texture
 * @param textureRect a sf::IntRect object help manipulate 2D axis aligned rectangles.
 */
SpriteNode::SpriteNode(const sf::Texture& texture, const sf::IntRect& textureRect)
    : mSprite(texture, textureRect)
{
}

/**
 * Draw the current SpriteNode object's sprite.
 * @param target a sf::RenderTarget& object indicates where we draw.
 * @param states a sf::RenderStates indicates the transform of the drawing object(mSprite).
 */
void SpriteNode::drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const
{
  target.draw(mSprite, states);
}