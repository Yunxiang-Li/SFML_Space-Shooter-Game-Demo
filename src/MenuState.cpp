// Include project header files
#include "MenuState.hpp"
#include "Utility.hpp"
#include "ResourceHolder.hpp"

// Include our Third-Party SFML header
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/View.hpp>

/**
 *
 * @param stack
 * @param context
 */
MenuState::MenuState(StateStack& stack, Context context)
    : State(stack, context)
    , mOptions()
    , mOptionIndex(0)
{
  // Get the menu state's background texture.
  sf::Texture& texture = context.textures -> get(Textures::TitleScreen);
  // Set the text font.
  sf::Font& font = context.fonts -> get(Fonts::Main);
  // Set the menu state's background sprite.
  mBackgroundSprite.setTexture(texture);

  // A simple menu demonstration

  // All settings for play option.
  sf::Text playOption;
  playOption.setFont(font);
  playOption.setString("Play");
  centerOrigin(playOption);
  playOption.setPosition(context.window -> getView().getSize() / 2.f);
  mOptions.push_back(playOption);

  // All settings for exit option.
  sf::Text exitOption;
  exitOption.setFont(font);
  exitOption.setString("Exit");
  centerOrigin(exitOption);
  exitOption.setPosition(playOption.getPosition() + sf::Vector2f(0.f, 30.f));
  mOptions.push_back(exitOption);
  // Present visual effects on all option text under menu state.
  updateOptionText();
}

/**
 * Draw the menu state's game world.
 */
void MenuState::draw()
{
  // Get the reference of the current render window.
  sf::RenderWindow& window = *getContext().window;

  window.setView(window.getDefaultView());
  // Draw the background sprite.
  window.draw(mBackgroundSprite);
  // Draw each option's text.
  for (const sf::Text& text : mOptions)
    window.draw(text);
}

/**
 * Just return true in menu state.(We do not need any update here).
 * @return a bool indicates the update process is always true.
 */
bool MenuState::update(sf::Time)
{
  return true;
}

/**
 * Process each menu options(User can use both mouse and arrow keys to select each option).
 * @param event a sf::Event object indicates each input event.
 * @return a bool value indicates whether the event is handled well.
 */
bool MenuState::handleEvent(const sf::Event& event)
{
  // The demonstration menu logic
  // Return false if event type is not a key pressed type.
  if (event.type != sf::Event::KeyPressed)
    return false;

  // Check if event type is sf::Keyboard::Return(Enter button).
  if (event.key.code == sf::Keyboard::Return)
  {
    // If play option is selected.
    if (mOptionIndex == Play)
    {
      // Request to quit the current menu state and push in-game state.
      requestStackPop();
      requestStackPush(States::Game);
    }
    // If exit option is selected.
    else if (mOptionIndex == Exit)
    {
      // The exit option was chosen, by removing itself, the stack will be empty, and the game will know it is time to close.
      requestStackPop();
    }
  }
  // Check if user press up arrow button.
  else if (event.key.code == sf::Keyboard::Up)
  {
    // Change the selected option's index.
    if (mOptionIndex > 0)
      mOptionIndex--;
    else
      mOptionIndex = mOptions.size() - 1;
    // Present visual effects on all option text under menu state.
    updateOptionText();
  }
    // Check if user press down arrow button.
  else if (event.key.code == sf::Keyboard::Down)
  {
    // Change the selected option's index.
    if (mOptionIndex < mOptions.size() - 1)
      mOptionIndex++;
    else
      mOptionIndex = 0;
    // Present visual effects on all option text under menu state.
    updateOptionText();
  }

  return true;
}

/**
 * Present visual effects on all option text under menu state.
 * Only the selected option is highlighted in red, and the remaining is in white.
 */
void MenuState::updateOptionText()
{
  if (mOptions.empty())
    return;

  // White all texts
  for (sf::Text& text : mOptions)
    text.setColor(sf::Color::White);

  // Red the selected text
  mOptions[mOptionIndex].setColor(sf::Color::Red);
}