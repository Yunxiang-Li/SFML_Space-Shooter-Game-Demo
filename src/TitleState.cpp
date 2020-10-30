// Include project header files
#include "TitleState.hpp"
#include "Utility.hpp"
#include "ResourceHolder.hpp"

// Include our Third-Party SFML header
#include <SFML/Graphics/RenderWindow.hpp>

/**
 * Constructor of TitleState class.
 * @param stack a StateStack object indicates the game state stack
 * @param context indicates a holder of shared objects between all states of the game
 */
TitleState::TitleState(StateStack& stack, Context context)
    : State(stack, context)
    , mText()
    , mShowText(true)
    , mTextEffectTime(sf::Time::Zero)
{
  // Set the background sprite.
  mBackgroundSprite.setTexture(context.textures -> get(Textures::TitleScreen));
  // Set the text font.
  mText.setFont(context.fonts -> get(Fonts::Main));
  // Set the text string content.
  mText.setString("Press any key to start");
  // Set title text's origin to be its center position.
  centerOrigin(mText);
  // Set the text position.
  mText.setPosition(context.window -> getView().getSize() / 2.f);
}

/**
 * Draw the title state's game world.
 */
void TitleState::draw()
{
  // Get the reference of the current render window.
  sf::RenderWindow& window = *(getContext().window);
  // Draw the background sprite.
  window.draw(mBackgroundSprite);
  // Draw the text if can.
  if (mShowText)
    window.draw(mText);
}

/**
 * Blink the title state's text and reset the title state's time.
 * @param dt a sf::Time indicates the delta time.
 * @return a bool indicates the update is successful.
 */
bool TitleState::update(sf::Time dt)
{
  // Add delta time to total display time.
  mTextEffectTime += dt;
  // Check if time is larger than or equal to 0.5.
  if (mTextEffectTime >= sf::seconds(0.5f))
  {
    // Enable/Disable the display of the text.
    mShowText = !mShowText;
    // Reset the text display time to be zero.
    mTextEffectTime = sf::Time::Zero;
  }

  return true;
}

/**
 * Handle trigger event to next game state.
 * @param event a sf::Event indicates each event input.
 * @return a bool value indicates the input event is handled.
 */
bool TitleState::handleEvent(const sf::Event& event)
{
  // If any key is pressed, trigger the next screen
  if (event.type == sf::Event::KeyPressed)
  {
    // Request to pop the current title state.
    requestStackPop();
    // Request to push the menu state.
    requestStackPush(States::Menu);
  }

  return true;
}