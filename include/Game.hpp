#ifndef GAME_H
#define GAME_H

// Include project header files
#include "World.hpp"
#include "Player.hpp"

// Include our Third-Party SFML header
#include <SFML/System/Time.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/RenderWindow.hpp>

/**
 *  Game class represents the game manager which inherits sf::NonCopyable class so that Game class is non-copyable.
 *  Game class's instances are non-copyable by explicitly disabling its copy constructor and its assignment operator.
 */
class Game : private sf::NonCopyable
{
 public:
  // Constructor.
  Game();

  // Public method that launches the whole game.
  void					run();

 // All private methods.
 private:
  // Method that processes player input.
  void					processInput();
  // Method that updates the game according to the time per frame(1/60 here since the FPS is 60).
  void					update(sf::Time elapsedTime);
  // Method that renders the game.
  void					render();
  // Update frame per second and time per update for us to debug(per real frame according to our platforms).
  void					updateStatistics(sf::Time elapsedTime);

 private:

  // A const sf::Time instance indicates time per frame.
  static const sf::Time	TimePerFrame;
  // A window object that can serve as a target for 2D drawing.
  sf::RenderWindow		mWindow;
  // A World object indicates the game world.
  World					mWorld;
  // A Player object to help handle events and real time input.
  Player				mPlayer;
  // Object for loading and manipulating character fonts
  sf::Font				mFont;
  // Graphical text that can be drawn to a render target
  sf::Text				mStatisticsText;
  // A const sf::Time instance indicates the interval time since last update(nearly 1 second in our program).
  sf::Time				mStatisticsUpdateTime;
  // std::size_t can store the maximum size of a theoretically possible object of any type (including array).
  // Here we store total frames per second here.
  std::size_t			mStatisticsNumFrames;
};

#endif // GAME_H