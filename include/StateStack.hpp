#ifndef STATESTACK_HPP
#define STATESTACK_HPP

// Include project header files
#include "State.hpp"
#include "StateIdentifiers.hpp"
#include "ResourceIdentifiers.hpp"

// Include our Third-Party SFML header
#include <SFML/System/NonCopyable.hpp>
#include <SFML/System/Time.hpp>

// Include C++ standard headers.
#include <vector>
#include <utility>
#include <functional>
#include <map>

// Forward declaration of sf::Event class and sf::RenderWindow class.
namespace sf
{
  class Event;
  class RenderWindow;
}

/**
 * This class represents all behaviour of the stack of game states which inherits sf::NonCopyable.
 */
class StateStack : private sf::NonCopyable
{
 public:
  // Use enum to represents a state action.
  enum Action
  {
    Push,
    Pop,
    Clear,
  };

 public:
  // Constructor.
  explicit			StateStack(State::Context context);

  // Create a specific game state and insert this state into the mFactories map.
  template <typename T>
  void				registerState(States::ID stateID);
  // Update each game state by delta time.
  void				update(sf::Time dt);
  // Draw each state one by one from the mStack.
  void				draw();
  // Handle each event in the mStack one by one.
  void				handleEvent(const sf::Event& event);
  // Add one game state to the mStack.
  void				pushState(States::ID stateID);
  // Remove one game state from the mStack.
  void				popState();
  // Clear the game state stack.
  void				clearStates();
  // Check if the stack of game states is empty.
  bool				isEmpty() const;

 private:
  // Takes an ID of a state and returns a smart pointer to the corresponding state class.
  State::Ptr		createState(States::ID stateID);
  // Apply pending changes to the specific game state stack(game state push, pop or clear).
  void				applyPendingChanges();

 private:
  // A struct indicates pending changes needed to be processed on the game state stack.
  struct PendingChange
  {
    // Constructor of the PendingChange struct.
    explicit			PendingChange(Action action, States::ID stateID = States::None);
    // An enum indicates an action that one pending change should perform.
    Action				action;
    // An enum indicates a specific game state's id.
    States::ID			stateID;
  };


 private:
  // A vector hold each unique_ptr to game state objects.
  std::vector<State::Ptr>								mStack;
  // Since we cannot add or remove element while loop the game stack we use another vector
  // to hold all PendingChange objects that indicates pending game state changes.
  std::vector<PendingChange>							mPendingList;
  // A holder of shared objects between all states of the game.
  State::Context										mContext;
  // Maps States::ID to those factory functions that create a new state on-demand.
  std::map<States::ID, std::function<State::Ptr()>>	    mFactories;
};

/**
 * A lambda expression acts as a factory for the state: It creates an object of the derived class T by passing the
 * stack and context to its constructor. This object is wrapped into a unique pointer and returned as
 * a base class pointer. The lambda expression is assigned to the corresponding state ID in the map.
 * @tparam T indicates derived state class we want to register
 * @param stateID States::ID indicates unique identifiers of each state
 */
template <typename T>
void StateStack::registerState(States::ID stateID)
{
  mFactories[stateID] = [this] ()
  {
    return State::Ptr(new T(*this, mContext));
  };
}

#endif // STATESTACK_HPP