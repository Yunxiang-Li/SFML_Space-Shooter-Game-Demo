#ifndef GAMESTATE_HPP
#define GAMESTATE_HPP

// Include project header files
#include "State.hpp"
#include "World.hpp"
#include "Player.hpp"

// Include our Third-Party SFML header
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Text.hpp>

/**
 * This class represents the in-game state which inherits State class.
 */
class GameState : public State
{
 public:
  // Constructor of GameState class.
  GameState(StateStack& stack, Context context);
  // Draw the game world.
  void		draw() override;
  // Update the game world according to the delta time.
  bool		update(sf::Time dt) override;
  // Handle each event in the game command queue.
  bool		handleEvent(const sf::Event& event) override;

 private:
  // A World object indicates the game world.
  World				mWorld;
  // A Player object reference indicates the game player(aircraft).
  Player&			mPlayer;
};

#endif // GAMESTATE_HPP