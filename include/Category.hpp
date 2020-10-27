#ifndef CATEGORY_HPP
#define CATEGORY_HPP

/**
 * Entity/scene node category by namespace, used to dispatch commands.
 */
namespace Category
{
  // Each category except None is initialized with an integer that has one bit set to 1, and the rest are set to 0.
  // This makes it possible to combine different categories with the bitwise OR operator.
  enum Type
  {
    None				= 0,
    Scene				= 1 << 0,
    PlayerAircraft		= 1 << 1,
    AlliedAircraft		= 1 << 2,
    EnemyAircraft		= 1 << 3,
  };
}

#endif // CATEGORY_HPP