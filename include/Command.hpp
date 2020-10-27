#ifndef COMMAND_HPP
#define COMMAND_HPP

// Include project header files
#include "Category.hpp"

// Include our Third-Party SFML header
#include <SFML/System/Time.hpp>

// Include C++ standard headers.
#include <functional>
#include <cassert>

// Forward declaration.
class SceneNode;

/**
 * This struct represents a command in this game.
 */
struct Command
{
  // Constructor.
  Command();

  // A std::function object indicates an action.
  std::function<void(SceneNode&, sf::Time)>	action;
  // An unsigned int indicates the category of the object which takes the action.
  unsigned int								category;
};

/**
 * Template for the action.
 * @tparam GameObject indicates the game object who do this action.
 * @tparam Function indicates the detailed action function.
 * @param fn a Function typename indicates the detailed action function.
 */
template <typename GameObject, typename Function>
std::function<void(SceneNode&, sf::Time)> derivedAction(Function fn)
{
  return [=] (SceneNode& node, sf::Time dt)
  {
    // Check if cast is safe(between a pointer of SceneNode object to a pointer of a GameObject object).
    assert(dynamic_cast<GameObject*>(&node) != nullptr);

    // Downcast node and invoke function on it
    fn(static_cast<GameObject&>(node), dt);
  };
}

#endif // COMMAND_HPP