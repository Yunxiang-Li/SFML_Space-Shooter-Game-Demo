#ifndef APPLICATION_HPP
#define APPLICATION_HPP

// Include project header files
#include "ResourceHolder.hpp"
#include "ResourceIdentifiers.hpp"
#include "Player.hpp"
#include "StateStack.hpp"

// Include our Third-Party SFML header
#include <SFML/System/Time.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Text.hpp>

/**
 *  Application class represents the game App manager which inherits sf::NonCopyable class so that Game
 *  class is non-copyable.
 *
 */
class Application
{
 public:
  // Constructor.
  Application();
  // Public method that launches the whole game.
  void					run();
  // Method that processes player input.
 private:
  // Method that processes player input.
  void					processInput();
  // Method that updates the game according to the time per frame(1/60 here since the FPS is 60).
  void					update(sf::Time dt);
  // Method that renders the game.
  void					render();
  // Update frame per second and time per update for us to debug(per real frame according to our platforms).
  void					updateStatistics(sf::Time dt);
  // Register all game states by initializing all the mStateStack member variable.
  void					registerStates();

 private:
  // A const sf::Time instance indicates time per frame.
  static const sf::Time	TimePerFrame;
  // A window object that can serve as a target for 2D drawing.
  sf::RenderWindow		mWindow;
  // A TextureHolder object to hold all textures we need to build the game world.
  TextureHolder			mTextures;
  // A FontHolder object to hold all fonts we need to build the game world.
  FontHolder			mFonts;
  // A Player object to help handle events and real time input.
  Player				mPlayer;
  // A StateStack object indicates the game state stack.
  StateStack			mStateStack;
  // Graphical text that can be drawn to a render target.
  sf::Text				mStatisticsText;
  // A const sf::Time instance indicates the interval time since last update(nearly 1 second in our program).
  sf::Time				mStatisticsUpdateTime;
  // std::size_t can store the maximum size of a theoretically possible object of any type (including array).
  // Here we store total frames per second here.
  std::size_t			mStatisticsNumFrames;
};

#endif // APPLICATION_HPP