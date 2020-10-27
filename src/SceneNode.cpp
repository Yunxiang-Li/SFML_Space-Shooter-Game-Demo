// Include project header files
#include "SceneNode.hpp"
#include "Command.hpp"

// Include standard library C++ libraries.
#include <algorithm>
#include <cassert>

/**
 * Constructor of the SceneNode class. Create the vector of unique_ptr<SceneNode> objects for child nodes
 * and set the pointer to the parent node to be nullptr.
 */
SceneNode::SceneNode()
    : mChildren()
    , mParent(nullptr)
{
}

/**
 * Attach one more child SceneNode object to the current SceneNode object.
 * @param child a Ptr(std::unique_ptr<SceneNode>) object which indicates the child node we want to add.
 */
void SceneNode::attachChild(Ptr child)
{
  // Assign input node's parent node to be the current node.
  child -> mParent = this;
  // Push the input node to be one of the current node's child node.
  mChildren.push_back(std::move(child));
}

/**
 * Try to get and remove one specific child SceneNode object from the current SceneNode object.
 * @param node indicates the specific node we want to get and remove.
 * @return a Ptr(std::unique_ptr<SceneNode>) object which represents the specific node we want to get and remove.
 */
SceneNode::Ptr SceneNode::detachChild(const SceneNode& node)
{
  // Use std::find_if method and lambda expression to try to find the iterator to the first element
  // in the range [first,last) for which pred returns true.
  auto found = std::find_if(mChildren.begin(), mChildren.end(), [&] (Ptr& p) -> bool
  // Check if the demanded node can be found in the mChildren vector(compare two pointers).
  { return p.get() == &node; });
  // Use assertion to check if the node is found.
  assert(found != mChildren.end());
  // Get and remove that node object.
  Ptr result = std::move(*found);
  // Set that node object's parent node to be nullptr.
  result -> mParent = nullptr;
  // Erase the nullptr unique_ptr from the vector.
  mChildren.erase(found);
  // Return that node object.
  return result;
}

/**
 * Update current SceneNode and all its children objects.
 * @param dt a sf::Time object indicates the current frame time.
 */
void SceneNode::update(sf::Time dt)
{
  updateCurrent(dt);
  updateChildren(dt);
}

void SceneNode::updateCurrent(sf::Time)
{
  // Do nothing by default
}

/**
 * Update all current node's children nodes.
 * @param dt a sf::Time object indicates the current frame time.
 */
void SceneNode::updateChildren(sf::Time dt)
{
  for(Ptr& child : this -> mChildren)
    child -> update(dt);
}

/**
 * Override from sf::Drawable to draw the object to a render target.
 * @param target indicates the sf::RenderTarget object we want to draw to
 * @param states indicates the current node's parent node's sf::RenderStates(altogether four states, the blend mode
 * , the transform, the texture, the shader) of the parent node.
 */
void SceneNode::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
  // *= here is overloaded by sf::Transform class to combine two transforms.
  // *= chains Parent's absolute transform with the current node's relative one.
  // Now, states.transform contains the absolute transform of the current node.
  states.transform *= getTransform();

  // Draw node and all its children with changed transform.
  drawCurrent(target, states);
  drawChildren(target, states);
}

void SceneNode::drawCurrent(sf::RenderTarget&, sf::RenderStates) const
{
  // Do nothing by default
}

/**
 * Draw each current node's child node by calling each child node's drawCurrent method.
 * @param target indicates the sf::RenderTarget object we want to draw to
 * @param states indicates the current node's sf::RenderStates(altogether four states, the blend mode
 * , the transform, the texture, the shader) of the parent node.
 */
void SceneNode::drawChildren(sf::RenderTarget& target, sf::RenderStates states) const
{
  for(const Ptr& child : this -> mChildren)
    child -> draw(target, states);
}

/**
 * Get current SceneNode object's global position. Overload of binary operator * to transform a point.
 * This call is equivalent to calling getWorldTransform().transformPoint(sf::Vector2f()).
 * @return a sf::Vector2f object indicates the transformed point.
 */
sf::Vector2f SceneNode::getWorldPosition() const
{
  return getWorldTransform() * sf::Vector2f();
}

/**
 * For each command, check whether current game object should receive and execute it or not.
 * @param command a Command object indicates each command.
 * @param dt a sf::Time object indicates the current frame time.
 */
void SceneNode::onCommand(const Command &command, sf::Time dt) {
  // First, we check if the current scene node is a receiver of the command, that is,
  // if it is listed in the command's receiver category.
  if (command.category & getCategory())
    // execute the command by invoking the action member of type std::function on the current node,
    // and with the current frame time.
    command.action(*this, dt);

  // Do the same thing for each children object of the current object.
  for (Ptr& child : mChildren)
    child -> onCommand(command, dt);
}

/**
 * Get current SceneNode object's global transform.
 * @return a sf::Transform object indicates current SceneNode object's transform.
 */
sf::Transform SceneNode::getWorldTransform() const
{
  // Initialize the current SceneNode object's transform to be the identity transform (does nothing).
  sf::Transform transform = sf::Transform::Identity;

  // Combine current's node's transform and all its parent nodes' transform together.
  for (const SceneNode* node = this; node != nullptr; node = node -> mParent)
    // Overload of binary operator * to combine two transforms.
    transform = node -> getTransform() * transform;

  return transform;
}

/**
 * Returns the category of the game object.(Category::Scene by default)
 * @return an unsigned int indicates the category of the game object.
 */
unsigned int SceneNode::getCategory() const
{
  // We return Category::Scene by default.
  return Category::Scene;
}