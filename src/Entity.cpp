// Include project header files
#include "Entity.hpp"

/**
 * Set current Entity object's velocity by a sf::Vector2f object.
 * @param velocity a sf::Vector2f object indicates the velocity of the current Entity object.
 */
void Entity::setVelocity(sf::Vector2f velocity)
{
  this -> mVelocity = velocity;
}

/**
 * Set current Entity object's velocity by two float.
 * @param vx a float indicates the velocity of current Entity object in x axis.
 * @param vy a float indicates the velocity of current Entity object in y axis.
 */
void Entity::setVelocity(float vx, float vy)
{
  this -> mVelocity.x = vx;
  this -> mVelocity.y = vy;
}

/**
 * Get current Entity object's velocity as a sf::Vector2f object. This method wont modify any member variables.
 * @return a sf::Vector2f object indicates the current Entity object's velocity.
 */
sf::Vector2f Entity::getVelocity() const
{
  return this -> mVelocity;
}

/**
 * Accelerate current Entity object by a sf::Vector2f object as velocity.
 * @param velocity a sf::Vector2f indicates the velocity needed to be accelerated.
 */
void Entity::accelerate(sf::Vector2f velocity)
{
  mVelocity += velocity;
}

/**
 * Accelerate current Entity object by two float as velocity.
 * @param vx a float indicates the velocity needed to be accelerated in x axis.
 * @param vy a float indicates the velocity needed to be accelerated in y axis.
 */
void Entity::accelerate(float vx, float vy)
{
  mVelocity.x += vx;
  mVelocity.y += vy;
}

/**
 * Update the movement of the current Entity object according to the delta time.
 * @param dt a sf::Time object indicates the current frame time.
 */
void Entity::updateCurrent(sf::Time dt)
{
  // Shortcut for setPosition(getPosition() + mVelocity * dt.asSeconds()).
  move(mVelocity * dt.asSeconds());
}
