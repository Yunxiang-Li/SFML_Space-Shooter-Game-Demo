// Include project header files
#include "World.hpp"

// Include our Third-Party SFML header
#include <SFML/Graphics/RenderWindow.hpp>

// Include C++ standard headers.
#include <cmath>

/**
 * Constructor of the World class.
 * @param window a sf::RenderWindow object indicates the window of the game.
 */
World::World(sf::RenderWindow& window)
    : mWindow(window)
    , mWorldView(window.getDefaultView())
    , mTextures()
    , mSceneGraph()
    , mSceneLayers()
    // We initialize view height to be 2000(just an arbitrary number).
    , mWorldBounds(0.f, 0.f, mWorldView.getSize().x, 2000.f)
    // Set player's plane's beginning position.
    , mSpawnPosition(mWorldView.getSize().x / 2.f, mWorldBounds.height - mWorldView.getSize().y / 2.f)
    // Scroll move upward.
    , mScrollSpeed(-50.f)
    , mPlayerAircraft(nullptr)
{
  // Call two methods for further initialization.
  loadTextures();
  buildScene();

  // Set view center initially matching the player's spawn position.
  mWorldView.setCenter(mSpawnPosition);
}

/**
 * Controls world scrolling and entity movement per delta time.
 * @param dt a sf::Time object indicates current frame time.
 */
void World::update(sf::Time dt)
{
  // Scroll the world in y axis direction(texture move from top to bottom) per delta time.
  mWorldView.move(0.f, mScrollSpeed * dt.asSeconds());

  // Reset the player's velocity to (0, 0).
  mPlayerAircraft -> setVelocity(0.f, 0.f);

  // Forward commands to scene graph, adapt velocity (scrolling, diagonal correction).
  while (!mCommandQueue.isEmpty())
    mSceneGraph.onCommand(mCommandQueue.pop(), dt);

  // Check and fix diagonal movement situations.
  this -> adaptPlayerVelocity();

  // Regular update step, adapt position (correct if outside view)
  mSceneGraph.update(dt);
  this -> adaptPlayerPosition();
}

/**
 * Draw all drawable game objects in the current game world.
 */
void World::draw()
{
  // Set window's view.
  mWindow.setView(mWorldView);
  // Draw all drawable objects to the window.
  mWindow.draw(mSceneGraph);
}

/**
 * Get the current command queue of the game.
 * @return a CommandQueue object indicates the current command queue of the game.
 */
CommandQueue& World::getCommandQueue()
{
  return this -> mCommandQueue;
}

/**
 * Load all textures we need for the game world.
 */
void World::loadTextures()
{
  mTextures.load(Textures::Eagle, "../Media/Textures/Eagle.png");
  mTextures.load(Textures::Raptor, "../Media/Textures/Raptor.png");
  mTextures.load(Textures::Desert, "../Media/Textures/Desert.png");
}

/**
 * Build the whole game world(scene).
 */
void World::buildScene()
{
  // First, initialize different layers.
  for (std::size_t i = 0; i < LayerCount; ++i)
  {
    // Create a new SceneNode object for each layer.
    SceneNode::Ptr layer(new SceneNode());
    // Assign each layer's SceneNode's pointer to mSceneLayers elements.
    mSceneLayers[i] = layer.get();
    // We set each layer's Ptr to be a child of mSceneGraph(A SceneNode object)
    mSceneGraph.attachChild(std::move(layer));
  }

  // Prepare the tiled background
  sf::Texture& texture = mTextures.get(Textures::Desert);
  // create a texture rect (with int coordinates) using the conversion from the world bounds
  // (which have the type sf::FloatRect and thus store float coordinates).
  sf::IntRect textureRect(mWorldBounds);
  // Enable the texture object to repeat itself.
  texture.setRepeated(true);

  // Add the background sprite to the scene
  // Create a new SpriteNode for background.
  std::unique_ptr<SpriteNode> backgroundSprite(new SpriteNode(texture, textureRect));
  // Set the beginning position of background.
  backgroundSprite -> setPosition(mWorldBounds.left, mWorldBounds.top);
  // Attach background sprite node as a child of background layer.
  mSceneLayers[Background] -> attachChild(std::move(backgroundSprite));

  // Add player's aircraft
  // First create a Aircraft object
  std::unique_ptr<Aircraft> leader(new Aircraft(Aircraft::Eagle, mTextures));
  mPlayerAircraft = leader.get();
  // Set Aircraft object's beginning position(just the spawn position of world).
  mPlayerAircraft -> setPosition(mSpawnPosition);
  // Set Aircraft object's speed(x direction speed is 40 to the right and y direction speed is same as scroll's speed).
  mPlayerAircraft -> setVelocity(40.f, mScrollSpeed);
  // Attach Aircraft as a child of air layer.
  mSceneLayers[Air] -> attachChild(std::move(leader));

  // Add two escorting aircrafts, placed relatively to the main plane.
  std::unique_ptr<Aircraft> leftEscort(new Aircraft(Aircraft::Raptor, mTextures));
  // Set left escorting aircraft beginning position(here position is relative to leader).
  leftEscort -> setPosition(-80.f, 50.f);
  // Attach left escorting aircraft to be one child.
  mPlayerAircraft -> attachChild(std::move(leftEscort));

  std::unique_ptr<Aircraft> rightEscort(new Aircraft(Aircraft::Raptor, mTextures));
  // Set right escorting aircraft beginning position(here position is relative to leader).
  rightEscort -> setPosition(80.f, 50.f);
  // Attach right escorting aircraft to be one child.
  mPlayerAircraft -> attachChild(std::move(rightEscort));
}

/**
 * Check and fix diagonal movement situations.
 */
void World::adaptPlayerVelocity()
{
  // Get current player's velocity.
  sf::Vector2f velocity = mPlayerAircraft -> getVelocity();

  // If moving diagonally, reduce velocity (to have always same velocity)
  if (velocity.x != 0.f && velocity.y != 0.f)
    mPlayerAircraft -> setVelocity(velocity / std::sqrt(2.f));

  // Add scrolling velocity(so that plane will stay at the same position if no movements involved).
  mPlayerAircraft -> accelerate(0.f, mScrollSpeed);
}

/**
 * Handle the case where the plane leaves the visible area of the screen.
 */
void World::adaptPlayerPosition()
{
  // Keep player's position inside the screen bounds, at least borderDistance units from the border
  sf::FloatRect viewBounds(mWorldView.getCenter() - mWorldView.getSize() / 2.f, mWorldView.getSize());

  // Least distance between view bound.
  const float borderDistance = 40.f;

  // Get player's current position.
  sf::Vector2f position = mPlayerAircraft -> getPosition();

  // Set player's position inside the screen bounds.
  position.x = std::max(position.x, viewBounds.left + borderDistance);
  position.x = std::min(position.x, viewBounds.left + viewBounds.width - borderDistance);
  position.y = std::max(position.y, viewBounds.top + borderDistance);
  position.y = std::min(position.y, viewBounds.top + viewBounds.height - borderDistance);
  mPlayerAircraft -> setPosition(position);
}