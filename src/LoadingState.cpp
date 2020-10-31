// Include project header files
#include "LoadingState.hpp"
#include "Utility.hpp"
#include "ResourceHolder.hpp"

// Include our Third-Party SFML header
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/View.hpp>

/**
 * Constructor of LoadingState class.
 * @param stack a StateStack object indicates the game state stack
 * @param context indicates a holder of shared objects between all states of the game
 */
LoadingState::LoadingState(StateStack& stack, Context context)
    : State(stack, context)
{
  // Get the current render window.
  sf::RenderWindow& window = *getContext().window;
  // Get the font.
  sf::Font& font = context.fonts -> get(Fonts::Main);
  // Get the current render window's view.
  sf::Vector2f viewSize = window.getView().getSize();
  // Set the loading text's font.
  mLoadingText.setFont(font);
  // Set the loading text's content.
  mLoadingText.setString("Loading Resources");
  // Put the loading text's origin at the center.
  centerOrigin(mLoadingText);
  // Set the loading text's position in the game world.
  mLoadingText.setPosition(viewSize.x / 2.f, viewSize.y / 2.f + 50.f);
  // Set progress bar's background's color to be white.
  mProgressBarBackground.setFillColor(sf::Color::White);
  // Set progress bar's background's size.
  mProgressBarBackground.setSize(sf::Vector2f(viewSize.x - 20, 10));
  // Set progress bar's background's position.
  mProgressBarBackground.setPosition(10, mLoadingText.getPosition().y + 40);

  // Set progress bar's color.
  mProgressBar.setFillColor(sf::Color(100,100,100));
  // Set progress bar's size.
  mProgressBar.setSize(sf::Vector2f(200, 10));
  // Set progress bar's position.
  mProgressBar.setPosition(10, mLoadingText.getPosition().y + 40);
  // Set progress bar's complete percents to be 0.
  setCompletion(0.f);

  mLoadingTask.execute();
}

void LoadingState::draw()
{
  sf::RenderWindow& window = *getContext().window;

  window.setView(window.getDefaultView());

  window.draw(mLoadingText);
  window.draw(mProgressBarBackground);
  window.draw(mProgressBar);
}

bool LoadingState::update(sf::Time)
{
  // Update the progress bar from the remote task or finish it
  if (mLoadingTask.isFinished())
  {
    requestStackPop();
    requestStackPush(States::Game);
  }
  else
  {
    setCompletion(mLoadingTask.getCompletion());
  }
  return true;
}

bool LoadingState::handleEvent(const sf::Event& event)
{
  return true;
}

void LoadingState::setCompletion(float percent)
{
  if (percent > 1.f) // clamp
    percent = 1.f;

  mProgressBar.setSize(sf::Vector2f(mProgressBarBackground.getSize().x * percent, mProgressBar.getSize().y));
}