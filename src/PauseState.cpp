// Include project header files
#include "PauseState.hpp"
#include "Utility.hpp"
#include "ResourceHolder.hpp"

// Include our Third-Party SFML header
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>

/**
 * Constructor of PauseState class.
 * @param stack a StateStack object indicates the game stack.
 * @param context indicates a holder of shared objects between all states of the game
 */
PauseState::PauseState(StateStack& stack, Context context)
    : State(stack, context)
    , mBackgroundSprite()
    , mPausedText()
    , mInstructionText()
{
  // Get the font.
  sf::Font& font = context.fonts -> get(Fonts::Main);
  // Get current view's size.
  sf::Vector2f viewSize = context.window -> getView().getSize();
  // Set the pause text font.
  mPausedText.setFont(font);
  // Set the pause string.
  mPausedText.setString("Game Paused");
  // Set the pause string size.
  mPausedText.setCharacterSize(70);
  // Set pause text's origin to be its center position.
  centerOrigin(mPausedText);
  // Set the pause string position.
  mPausedText.setPosition(0.5f * viewSize.x, 0.4f * viewSize.y);
  // Set the instruction text font.
  mInstructionText.setFont(font);
  // Set the instruction text string.
  mInstructionText.setString("(Press Backspace to return to the main menu)");
  // Set instruction text's origin to be its center position.
  centerOrigin(mInstructionText);
  mInstructionText.setPosition(0.5f * viewSize.x, 0.6f * viewSize.y);
}

/**
 * Draw the screen of PauseState.
 */
void PauseState::draw()
{
  // Get the current render window.
  sf::RenderWindow& window = *getContext().window;
  // Set render window's view.
  window.setView(window.getDefaultView());
  // Create a sf::RectangleShape to present a transparent rectangle background shape.
  sf::RectangleShape backgroundShape;
  // Set the background shape's color to be transparent.
  backgroundShape.setFillColor(sf::Color(0, 0, 0, 150));
  // Set the background shape's size to be the same as window's current size.
  backgroundShape.setSize(window.getView().getSize());
  // Draw the background shape.
  window.draw(backgroundShape);
  // Draw the paused text.
  window.draw(mPausedText);
  // Draw the instruction text.
  window.draw(mInstructionText);
}

/**
 * Always return false so that the game is actually paused.
 * @return a bool value to pause the game.
 */
bool PauseState::update(sf::Time)
{
  return false;
}

/**
 * Handle each event according to the key user pressed.
 * @param event a sf::Event object indicates each input event.
 * @return a bool value indicates that the game is always paused in pause state.
 */
bool PauseState::handleEvent(const sf::Event& event)
{
  // If no key is pressed, return false.
  if (event.type != sf::Event::KeyPressed)
    return false;

  // If escape pressed, remove pause state to return to the in-game state.
  if (event.key.code == sf::Keyboard::Escape)
  {
    requestStackPop();
  }

  // If backspace pressed, clear all game states and return to the main menu.
  if (event.key.code == sf::Keyboard::BackSpace)
  {
    requestStateClear();
    requestStackPush(States::Menu);
  }

  return false;
}