#ifndef PLAYER_HPP
#define PLAYER_HPP

// Include project header files
#include "Command.hpp"

// Include our Third-Party SFML header
#include <SFML/Window/Event.hpp>

// Include C++ standard headers.
#include <map>

// Forward declaration of CommandQueue.
class CommandQueue;

/**
 * This class handles all real time input and events(except quit game event).
 */
class Player
{
 public:
  // Use enum to represent each action.
  enum Action
  {
    MoveLeft,
    MoveRight,
    MoveUp,
    MoveDown,
    ActionCount
  };

 public:
  // Constructor of Player class.
  Player();
  // Creates a command for each event.
  void					handleEvent(const sf::Event& event, CommandQueue& commands);
  // Creates a command every frame an arrow key is held down.
  void					handleRealtimeInput(CommandQueue& commands);
  // Set and the key mapped to a specific action.
  void					assignKey(Action action, sf::Keyboard::Key key);
  // Get and the key mapped to a specific action.
  sf::Keyboard::Key		getAssignedKey(Action action) const;

 private:
  void					initializeActions();
  static bool			isRealtimeAction(Action action);

 private:
  // A std::map between keys and Action enum.
  std::map<sf::Keyboard::Key, Action>		mKeyBinding;
  // A std::map between Action enum and Command objects.
  std::map<Action, Command>				    mActionBinding;
};

#endif // PLAYER_HPP