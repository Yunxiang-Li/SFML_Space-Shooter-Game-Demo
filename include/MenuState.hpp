#ifndef MENUSTATE_HPP
#define MENUSTATE_HPP

// Include project header files
#include "State.hpp"

// Include our Third-Party SFML header
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Text.hpp>

/**
 * This class represents the menu state which inherits State class.
 */
class MenuState : public State
{
 public:
  // Constructor of MenuState class.
  MenuState(StateStack& stack, Context context);
  // Draw the menu state's game world.
  void			draw() override;
  // Just return true in menu state.(We do not need any update here)
  bool			update(sf::Time dt) override;
  // Process each menu options.
  bool			handleEvent(const sf::Event& event) override;
  // Present visual effects on all option text under menu state.
  void			updateOptionText();

 private:
  // An enum indicates all options under menu state.
  enum OptionNames
  {
    Play,
    Exit,
  };

 private:
  // A sf::Sprite indicates the background sprite.
  sf::Sprite				mBackgroundSprite;
  // A vector of sf::Text objects indicates all options under menu state.
  std::vector<sf::Text>	    mOptions;
  // A std::size_t value indicates the index of the specific option in the mOptions vector.
  std::size_t				mOptionIndex;
};

#endif // MENUSTATE_HPP