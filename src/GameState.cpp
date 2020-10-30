// Include project header files
#include "GameState.hpp"

/**
 * Constructor of GameState class.
 * @param stack a StateStack object indicates the game state stack
 * @param context indicates a holder of shared objects between all states of the game
 */
GameState::GameState(StateStack& stack, Context context)
    : State(stack, context)
    , mWorld(*context.window)
    , mPlayer(*context.player)
{
}

/**
 * Draw the game world.
 */
void GameState::draw()
{
  mWorld.draw();
}

/**
 * Update the game world according to the delta time.
 * @param dt a sf::Time object indicates the delta time.
 * @return a bool value indicates that game world is updated successfully.
 */
bool GameState::update(sf::Time dt)
{
  mWorld.update(dt);

  CommandQueue& commands = mWorld.getCommandQueue();
  mPlayer.handleRealtimeInput(commands);

  return true;
}

/**
 * Handle each event in the game command queue.
 * @param event a sf::Event object indicates an event.
 * @return a bool value indicates that the event is handled successfully.
 */
bool GameState::handleEvent(const sf::Event& event)
{
  // Game input handling
  CommandQueue& commands = mWorld.getCommandQueue();
  mPlayer.handleEvent(event, commands);

  // Escape pressed, trigger the pause screen
  if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)
    requestStackPush(States::Pause);

  return true;
}