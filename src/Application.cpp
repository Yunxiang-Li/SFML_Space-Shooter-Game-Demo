// Project header files
#include "Application.hpp"
#include "Utility.hpp"
#include "State.hpp"
#include "StateIdentifiers.hpp"
#include "TitleState.hpp"
#include "GameState.hpp"
#include "MenuState.hpp"
#include "PauseState.hpp"

// Initialize time for per frame to be 1/60 which means our game's FPS(frame per second) is 60.
const sf::Time Application::TimePerFrame = sf::seconds(1.f/60.f);

/**
 * Constructor of Application class.
 */
Application::Application()
    : mWindow(sf::VideoMode(640, 480), "States", sf::Style::Close)
    , mTextures()
    , mFonts()
    , mPlayer()
    , mStateStack(State::Context(mWindow, mTextures, mFonts, mPlayer))
    , mStatisticsText()
    , mStatisticsUpdateTime()
    , mStatisticsNumFrames(0)
{
  // If key repeat is enabled, we will receive repeated KeyPressed events while keeping a key pressed.
  mWindow.setKeyRepeatEnabled(false);

  // Load font and title screen texture.
  mFonts.load(Fonts::Main, "../Media/Sansation.ttf");
  mTextures.load(Textures::TitleScreen, "../Media/Textures/TitleScreen.png");
  // Set the graphical text's font.
  mStatisticsText.setFont(mFonts.get(Fonts::Main));
  // Set the graphical text's position.
  mStatisticsText.setPosition(5.f, 5.f);
  // Set the graphical text's character size.
  mStatisticsText.setCharacterSize(10u);
  // Register all game states.
  registerStates();
  // Push current state(Title state) to the state stack.
  mStateStack.pushState(States::Title);
}

/**
 * Main loop of the game.
 */
void Application::run()
{
  // Use a Clock object to control and get access to the elapsed time.
  sf::Clock clock;
  // Initialize the update interval to be zero.
  sf::Time timeSinceLastUpdate = sf::Time::Zero;

  // Enable or disable vertical synchronization.
  //Activating vertical synchronization will limit the number of frames displayed to the refresh rate of the monitor.
  //This can avoid some visual artifacts, and limit the framerate to a good value.
  mWindow.setVerticalSyncEnabled(true);

  // When the game is still running.
  while (mWindow.isOpen())
  {
    // Get the elapsed time and reset the clock.
    sf::Time dt = clock.restart();
    // Get the update interval.
    timeSinceLastUpdate += dt;
    // We divide update interval to a bunch of time for per frame.
    // We deal with each time per frame.
    while (timeSinceLastUpdate >= TimePerFrame)
    {
      timeSinceLastUpdate -= TimePerFrame;
      // Process input.
      processInput();
      // Update the game for each frame.
      update(TimePerFrame);

      // Check inside this loop, because stack might be empty before update() call
      if (mStateStack.isEmpty())
        mWindow.close();
    }
    // Update relative graphical texts per real frame according to the elapsed time.
    updateStatistics(dt);
    // Render the window.
    render();
  }
}

/**
 * This method handles user input. It polls the application window for any input events.
 */
void Application::processInput()
{
  sf::Event event{};
  // Loop if there is still at least one event left.
  while (mWindow.pollEvent(event))
  {
    // Handle each event.
    mStateStack.handleEvent(event);
    // Check if player wants to click the 'x' button and quit the game.
    if (event.type == sf::Event::Closed)
      mWindow.close();
  }
}

/**
 * Move the spaceship according to what direction keys user has pressed.
 * @param dt a sf::Time object indicates the time passed since last update time.
 */
void Application::update(sf::Time dt)
{
  mStateStack.update(dt);
}

/**
 * Render our game(sprites) to the screen.
 */
void Application::render()
{
  // Clear the entire 2d window with a default black color.
  mWindow.clear();
  // Draw the whole game world.
  mStateStack.draw();
  // Set view to be the current whole window(So text will always be in the top left corner).
  mWindow.setView(mWindow.getDefaultView());
  // Draw the Text exhibition of the current frame to the window.
  mWindow.draw(mStatisticsText);
  // Display the window(then we can see the result).
  mWindow.display();
}

/**
 * Update frame per second and time per update for us to debug. elapsedTime here means time interval since last update.
 * @param dt a sf::Time object indicates the time passed since last update time.
 */
void Application::updateStatistics(sf::Time dt)
{
  // Add this time's interval since last update to the interval left from previous times.
  mStatisticsUpdateTime += dt;
  // Add one frame.
  mStatisticsNumFrames += 1;

  // We update graphical texts per second.
  if (mStatisticsUpdateTime >= sf::seconds(1.0f))
  {
    // Set frames per second and time per update.
    mStatisticsText.setString("FPS: " + toString(mStatisticsNumFrames));
    // Minus one second.
    mStatisticsUpdateTime -= sf::seconds(1.0f);
    // Reset total frames to be zero.
    mStatisticsNumFrames = 0;
  }
}

/**
 * Register all game states by initializing all the mStateStack member variable.
 */
void Application::registerStates()
{
  mStateStack.registerState<TitleState>(States::Title);
  mStateStack.registerState<MenuState>(States::Menu);
  mStateStack.registerState<GameState>(States::Game);
  mStateStack.registerState<PauseState>(States::Pause);
}