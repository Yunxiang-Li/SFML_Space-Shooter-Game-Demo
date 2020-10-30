#ifndef TITLESTATE_HPP
#define TITLESTATE_HPP

// Include project header files
#include "State.hpp"

// Include our Third-Party SFML header
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Text.hpp>

/**
 * This class represents the title state which inherits State class.
 */
class TitleState : public State
{
 public:
  // Constructor of TitleState class.
  TitleState(StateStack& stack, Context context);
  // Draw the title state's game world.
  void		draw() override;
  // Hide the title state's text and reset the title state's time.
  bool		update(sf::Time dt) override;
  // Handle trigger event to next game state.
  bool		handleEvent(const sf::Event& event) override;


 private:
  // A sf::Sprite object indicates the background sprite of the title state.
  sf::Sprite		mBackgroundSprite;
  // A sf::Text object indicates the text in the title state.
  sf::Text			mText;
  // A bool value indicates whether title state's text can be displayed.
  bool				mShowText;
  // A sf::Time indicates how long title state's text is displayed.
  sf::Time			mTextEffectTime;
};

#endif // TITLESTATE_HPP