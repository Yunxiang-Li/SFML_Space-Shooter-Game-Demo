#ifndef ENTITY_HPP
#define ENTITY_HPP

// Include project header files
#include "SceneNode.hpp"

/**
 * Entity class contains the data and functionality that all different kinds of entities have in common.
 * Entity class also inherits the SceneNode class.
 */
class Entity : public SceneNode
{
 public:
  // Set current Entity object's velocity by a sf::Vector2f object.
  void				setVelocity(sf::Vector2f velocity);
  // Set current Entity object's velocity by two float.
  void				setVelocity(float vx, float vy);
  // Accelerate current Entity object.
  void				accelerate(sf::Vector2f velocity);
  void				accelerate(float vx, float vy);

  // Get current Entity object's velocity as a sf::Vector2f object. This method wont modify any member variables.
  sf::Vector2f		getVelocity() const;

 private:
  // updateCurrent method from SceneNode class to update the movement of
  // the current Entity object according to the delta time.
  void		updateCurrent(sf::Time dt) override;

 private:
  // A sf::Vector2f object which represents the velocity of the current Entity object.
  sf::Vector2f		mVelocity;
};

#endif // ENTITY_HPP