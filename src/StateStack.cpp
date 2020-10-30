// Include project header files
#include "StateStack.hpp"

// Include C++ standard headers.
#include <cassert>

/**
 * Constructor of StateStack class.
 * @param context indicates a holder of shared objects between all states of the game
 */
StateStack::StateStack(State::Context context)
    : mStack()
    , mPendingList()
    , mContext(context)
    , mFactories()
{
}

/**
 * Update each game state by delta time.
 * @param dt a sf::Time object indicates the delta time.
 */
void StateStack::update(sf::Time dt)
{
  // Iterate from top to bottom, stop as soon as update() returns false
  for (auto itr = mStack.rbegin(); itr != mStack.rend(); ++itr)
  {
    if (!(*itr) -> update(dt))
      break;
  }
  // Apply pending changes to the specific game state stack(game state push, pop or clear).
  applyPendingChanges();
}

/**
 * Draw each state one by one from the mStack.
 */
void StateStack::draw()
{
  // Draw all active states from bottom to top
  for (State::Ptr& state : mStack)
    state -> draw();
}

/**
 * Handle each event in the mStack one by one.
 * @param event a sf::Event object indicates each event we need to deal with.
 */
void StateStack::handleEvent(const sf::Event& event)
{
  // Iterate from top to bottom, stop as soon as handleEvent() returns false
  for (auto itr = mStack.rbegin(); itr != mStack.rend(); ++itr)
  {
    // Check if the specific state can handle that specific event.
    if (!(*itr) -> handleEvent(event))
      break;
  }
  // Apply pending changes to the specific game state stack(game state push, pop or clear).
  applyPendingChanges();
}

/**
 * Add one game state to the state stack.
 * @param stateID a enum indicates the ID of the game state.
 */
void StateStack::pushState(States::ID stateID)
{
  mPendingList.push_back(PendingChange(Push, stateID));
}

/**
 * Remove one game state from the state stack.
 */
void StateStack::popState()
{
  mPendingList.push_back(PendingChange(Pop));
}

/**
 * Clear the game state stack.
 */
void StateStack::clearStates()
{
  mPendingList.push_back(PendingChange(Clear));
}

/**
 * Check if the stack of game states is empty.
 * @return a bool indicates whether the game state is empty or not.
 */
bool StateStack::isEmpty() const
{
  return mStack.empty();
}

/**
 * Takes an ID of a state and returns a smart pointer to the corresponding state class.
 * First looking up the ID in the map and invoking the stored std::function factory,
 * which returns the std::unique_ptr to the State base class.
 * @param stateID a enum indicates the game state id.
 * @return a unique_ptr to the specific game state.
 */
State::Ptr StateStack::createState(States::ID stateID)
{
  auto found = mFactories.find(stateID);
  // Ensure that we can find the state with specific id.
  assert(found != mFactories.end());

  return found -> second();
}

/**
 * Apply pending changes(game state push, pop or clear).
 */
void StateStack::applyPendingChanges()
{
  // Apply each pending change.
  for (PendingChange change : mPendingList)
  {
    // Check the appending change type.
    switch (change.action)
    {
      case Push:
        mStack.push_back(createState(change.stateID));
        break;

      case Pop:
        mStack.pop_back();
        break;

      case Clear:
        mStack.clear();
        break;
    }
  }
  // Clear the pending list.
  mPendingList.clear();
}

/**
 * Constructor of PendingChange struct.
 * @param action an action enum indicates one specific action of game stack(push, pop, clear).
 * @param stateID an enum indicates the id of a specific game state.
 */
StateStack::PendingChange::PendingChange(Action action, States::ID stateID)
    : action(action)
    , stateID(stateID)
{
}