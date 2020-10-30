#ifndef PAUSESTATE_HPP
#define PAUSESTATE_HPP

// Include project header files
#include "State.hpp"

// Include our Third-Party SFML header
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Text.hpp>

/**
 * This class represents the pause state which inherits State class.
 */
class PauseState : public State
{
 public:
  // Constructor of PauseState class.
  PauseState(StateStack& stack, Context context);
  //  Draw the screen of PauseState.
  void		draw() override;
  // Always return false so that the game is actually paused.
  bool		update(sf::Time dt) override;
  // Handle each event according to the key user pressed.
  bool		handleEvent(const sf::Event& event) override;


 private:
  // A sf::Sprite object indicates the background sprite of the pause state.
  sf::Sprite		mBackgroundSprite;
  // A sf::Text object indicates the paused text.
  sf::Text			mPausedText;
  // A sf::Text object indicates the instruction text.
  sf::Text			mInstructionText;
};

#endif // PAUSESTATE_HPP
