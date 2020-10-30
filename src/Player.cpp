// Include project header files
#include "Player.hpp"
#include "CommandQueue.hpp"
#include "Aircraft.hpp"

// A AircraftMover struct helps us to change the aircraft's velocity if an arrow key is pressed.
struct AircraftMover
{
  // Store the velocity we want to add to a Aircraft object.
  sf::Vector2f velocity;

  // Constructor of AircraftMover struct.
  AircraftMover(float vx, float vy)
      : velocity(vx, vy)
  {
  }

  // Functor which adds velocity to a Aircraft object.
  void operator() (Aircraft& aircraft, sf::Time) const
  {
    aircraft.accelerate(velocity);
  }
};

// Constructor of Player class.
Player::Player()
{
  // Set initial key bindings(bind key with actions).
  mKeyBinding[sf::Keyboard::Left] = MoveLeft;
  mKeyBinding[sf::Keyboard::Right] = MoveRight;
  mKeyBinding[sf::Keyboard::Up] = MoveUp;
  mKeyBinding[sf::Keyboard::Down] = MoveDown;

  // Set initial action bindings
  initializeActions();

  // Assign all categories to player's aircraft
  for (auto& pair : mActionBinding)
  pair.second.category = Category::PlayerAircraft;
}

/**
 * Creates a command for each event.
 * @param event a sf::Event object indicates each event.
 * @param commands a CommandQueue object indicates current queue of commands.
 */
void Player::handleEvent(const sf::Event& event, CommandQueue& commands)
{
  // Check whether a key is pressed.
  if (event.type == sf::Event::KeyPressed)
  {
    // Check if pressed key appears in key binding, trigger command if so.
    auto found = mKeyBinding.find(event.key.code);
    if (found != mKeyBinding.end() && !isRealtimeAction(found -> second))
      commands.push(mActionBinding[found -> second]);
  }
}

/**
 * Creates a command every frame an arrow key is held down.
 * @param commands a CommandQueue object indicates current queue of commands.
 */
void Player::handleRealtimeInput(CommandQueue& commands)
{
  // Traverse all assigned keys and check if they are pressed
  for (auto pair : mKeyBinding)
  {
    // If key is pressed, lookup action and trigger corresponding command
    if (sf::Keyboard::isKeyPressed(pair.first) && isRealtimeAction(pair.second))
      commands.push(mActionBinding[pair.second]);
  }
}

/**
 * Set and the key mapped to a specific action.
 * @param action a Action enum indicates an action to the game object.
 * @param key a sf::Keyboard::Key object indicates a key on the keyboard.
 */
void Player::assignKey(Action action, sf::Keyboard::Key key)
{
  // Remove all keys that already map to action
  for (auto itr = mKeyBinding.begin(); itr != mKeyBinding.end(); )
  {
    if (itr -> second == action)
      mKeyBinding.erase(itr++);
    else
      ++itr;
  }

  // Insert new binding.
  mKeyBinding[key] = action;
}

/**
 * Get and the key mapped to a specific action.
 * @param action a Action enum indicates an action to the game object.
 * @return a sf::Keyboard::Key object indicates a key on the keyboard.
 */
sf::Keyboard::Key Player::getAssignedKey(Action action) const
{
  for (auto pair : mKeyBinding)
  {
    if (pair.second == action)
      return pair.first;
  }
  // If no specific keys are bound, return sf::Keyboard::Unknown.
  return sf::Keyboard::Unknown;
}

/**
 *  Initialize mActionBinding map of the Player object.
 */
void Player::initializeActions()
{
  const float playerSpeed = 200.f;

  // Set each action's mapping command function.
  mActionBinding[MoveLeft].action	 = derivedAction<Aircraft>(AircraftMover(-playerSpeed, 0.f));
  mActionBinding[MoveRight].action   = derivedAction<Aircraft>(AircraftMover(+playerSpeed, 0.f));
  mActionBinding[MoveUp].action      = derivedAction<Aircraft>(AircraftMover(0.f, -playerSpeed));
  mActionBinding[MoveDown].action    = derivedAction<Aircraft>(AircraftMover(0.f, +playerSpeed));
}

/**
 * Check if input Action enum is a real time action.
 * @param action a Action enum indicates an action.
 * @return a bool value indicates whether the input action is a real time action or not.
 */
bool Player::isRealtimeAction(Action action)
{
  switch (action)
  {
    case MoveLeft:
    case MoveRight:
    case MoveDown:
    case MoveUp:
      return true;

    default:
      return false;
  }
}