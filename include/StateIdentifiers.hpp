#ifndef STATEIDENTIFIERS_HPP
#define STATEIDENTIFIERS_HPP

/**
 * This namespace hold unique identifiers of all states in the game by an enum States.
 */
namespace States
{
  enum ID
  {
    None,
    Title,
    Menu,
    Game,
    Loading,
    Pause
  };
}

#endif // STATEIDENTIFIERS_HPP