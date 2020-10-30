// Include project header files
#include "State.hpp"
#include "StateStack.hpp"

/**
 * Constructor of a Context struct. A struct indicates a holder of shared objects between all states of the game.
 * @param window
 * @param textures
 * @param fonts
 * @param player
 */
State::Context::Context(sf::RenderWindow& window, TextureHolder& textures, FontHolder& fonts, Player& player)
    : window(&window)
    , textures(&textures)
    , fonts(&fonts)
    , player(&player)
{
}

/**
 * Constructor of State class.
 * @param stack A StateStack object indicates the game state stack.
 * @param context a Context struct indicates a holder of shared objects between all states of the game.
 */
State::State(StateStack& stack, Context context)
    : mStack(&stack)
    , mContext(context)
{
}

// Set virtual destructor of State class to default.
State::~State()= default;

/**
 * Push current state to the game state stack.
 * @param stateID an enum indicates pushed state's id.
 */
void State::requestStackPush(States::ID stateID)
{
  mStack -> pushState(stateID);
}

/**
 * Pop current state from the game state stack.
 */
void State::requestStackPop()
{
  mStack -> popState();
}

/**
 * Clear the game state stack.
 */
void State::requestStateClear()
{
  mStack -> clearStates();
}

/**
 * Get current state object's Context member.
 * @return a Context struct indicates a holder of shared objects between all states of the game.
 */
State::Context State::getContext() const
{
  return mContext;
}