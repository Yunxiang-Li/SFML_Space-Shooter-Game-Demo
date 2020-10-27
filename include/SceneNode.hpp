#ifndef SCENENODE_HPP
#define SCENENODE_HPP

// Include project header files
#include "Command.hpp"
// Include our Third-Party SFML header
#include <SFML/System/NonCopyable.hpp>
#include <SFML/System/Time.hpp>
#include <SFML/Graphics/Transformable.hpp>
#include <SFML/Graphics/Drawable.hpp>

// Include standard library C++ libraries.
#include <vector>
#include <memory>

/**
 *  This virtual class represents a scene manipulation object
 *  which inherits sf::Transformable, sf::Drawable and sf::NonCopyable class.
 */
class SceneNode : public sf::Transformable, public sf::Drawable, public sf::NonCopyable
{
 public:
  // Use 'Ptr' to indicates an unique_ptr to a SceneNode object.
  typedef std::unique_ptr<SceneNode> Ptr;

 public:
  // Constructor
  SceneNode();

  // Attach one more child SceneNode object to the current SceneNode object.
  void					attachChild(Ptr child);
  // Try to get and remove one specific child SceneNode object from the current SceneNode object.
  Ptr					detachChild(const SceneNode& node);
  // Update current SceneNode and all its children objects.
  void					update(sf::Time dt);
  // Get current SceneNode object's global position.
  sf::Vector2f			getWorldPosition() const;
  // Get current SceneNode object's global transform.
  sf::Transform			getWorldTransform() const;
  // For each command, check whether current game object should receive and execute it or not.
  void					onCommand(const Command& command, sf::Time dt);
  // Virtual method to returns the category of the game object(Category::Scene by default).
  virtual unsigned int	getCategory() const;

 private:
  // Virtual method to update the current SceneNode object.
  virtual void			updateCurrent(sf::Time dt);
  // Update all current node's children nodes.
  void					updateChildren(sf::Time dt);
  // Override from sf::Drawable to draw the object to a render target.
  virtual void			draw(sf::RenderTarget& target, sf::RenderStates states) const;
  // Virtual method that only draws the current object (but not the children).
  virtual void			drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const;
  // Draw each current node's child node by calling each child node's drawCurrent method.
  void					drawChildren(sf::RenderTarget& target, sf::RenderStates states) const;


 private:
  // A vector of unique_ptr<SceneNode> objects to store all child nodes.
  std::vector<Ptr>		mChildren;
  // A pointer to a SceneNode object which represents parent node.
  SceneNode*			mParent;
};

#endif // SCENENODE_HPP
