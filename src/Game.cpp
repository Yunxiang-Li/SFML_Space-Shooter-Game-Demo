// Project header files
#include "Game.hpp"
#include "StringHelpers.hpp"

// Initialize time for per frame to be 1/60 which means our game's FPS(frame per second) is 60.
const sf::Time Game::TimePerFrame = sf::seconds(1.f/60.f);

// Constructor of the Game object with members initialization list.
Game::Game()
    : mWindow(sf::VideoMode(640, 480), "Space Shooter", sf::Style::Close)
    , mWorld(mWindow)
    , mPlayer()
    , mFont()
    , mStatisticsText()
    , mStatisticsUpdateTime(sf::Time(sf::Time::Zero))
    , mStatisticsNumFrames(0)
{

  // Try to import the Sansation.ttf file.
  if (!mFont.loadFromFile("../Media/Sansation.ttf"))
  {
    // Else output error message.
    std::cout <<"No ttf file found for the Sansation.ttf" << std::endl;
    exit(EXIT_FAILURE);
  }
  // Set the graphical text's font.
  mStatisticsText.setFont(mFont);
  // Set the graphical text's position.
  mStatisticsText.setPosition(5.f, 5.f);
  // Set the graphical text's character size.
  mStatisticsText.setCharacterSize(10);
}

/**
 * Main loop of the game.
 */
void Game::run()
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
    sf::Time elapsedTime = clock.restart();
    // Get the update interval.
    timeSinceLastUpdate += elapsedTime;
    // We divide update interval to a bunch of time for per frame.
    // We deal with each time per frame.
    while (timeSinceLastUpdate >= TimePerFrame)
    {
      timeSinceLastUpdate -= TimePerFrame;
      // Process input.
      processInput();
      // Update the game for each frame.
      update(TimePerFrame);
    }
    // Update relative graphical texts per real frame according to the elapsed time.
    updateStatistics(elapsedTime);
    // Render the window.
    render();
  }
}

/**
 * This method handles user input. It polls the application window for any input events.
 */
void Game::processInput()
{
  CommandQueue& commands = mWorld.getCommandQueue();
  sf::Event event{};

  // Loop if there is still at least one event left.
  while (mWindow.pollEvent(event))
  {
    // Handle each event.
    mPlayer.handleEvent(event, commands);

    // Check if player wants to click the 'x' button and quit the game.
    if (event.type == sf::Event::Closed)
      mWindow.close();

  }
  // Handle real time input.
  mPlayer.handleRealtimeInput(commands);
}

/**
 * Move the spaceship according to what direction keys user has pressed.
 */
void Game::update(sf::Time elapsedTime)
{
  mWorld.update(elapsedTime);
}

/**
 * Render our game(sprites) to the screen.
 */
void Game::render()
{
  // Clear the entire 2d window with a default black color.
  mWindow.clear();
  // Draw the whole game world.
  mWorld.draw();
  // Set view to be the current whole window(So text will always be in the top left corner).
  mWindow.setView(mWindow.getDefaultView());
  // Draw the Text exhibition of the current frame to the window.
  mWindow.draw(mStatisticsText);
  // Display the window(then we can see the result).
  mWindow.display();
}

/**
 * Update frame per second and time per update for us to debug. elapsedTime here means time interval since last update.
 */
void Game::updateStatistics(sf::Time elapsedTime)
{
  // Add this time's interval since last update to the interval left from previous times.
  mStatisticsUpdateTime += elapsedTime;
  // Add one frame.
  mStatisticsNumFrames += 1;

  // We update graphical texts per second.
  if (mStatisticsUpdateTime >= sf::seconds(1.0f))
  {
    // Set frames per second and time per update.
    mStatisticsText.setString(
            // Frame per second.
        "Frames / Second = " + toString(mStatisticsNumFrames) + "\n" +
            // Average time (microseconds) for one update.
            "Time / Update = " + toString(mStatisticsUpdateTime.asMicroseconds() / mStatisticsNumFrames) + "us");
    // Minus one second.
    mStatisticsUpdateTime -= sf::seconds(1.0f);
    // Reset total frames to be zero.
    mStatisticsNumFrames = 0;
  }
}
