#ifndef WORLD_HPP
#define WORLD_HPP

// Include project header files
#include "ResourceHolder.hpp"
#include "ResourceIdentifiers.hpp"
#include "SceneNode.hpp"
#include "SpriteNode.hpp"
#include "Aircraft.hpp"
#include "CommandQueue.hpp"
#include "Command.hpp"

// Include our Third-Party SFML header
#include <SFML/System/NonCopyable.hpp>
#include <SFML/Graphics/View.hpp>
#include <SFML/Graphics/Texture.hpp>

// Include C++ standard headers.
#include <array>
#include <queue>

// Forward declaration
namespace sf
{
  class RenderWindow;
}

/**
 * This class represents the world of all game objects(except fonts) which inherits sf::NonCopyable
 * Since we only have one world and we don't want it to be copied.
 */
class World : private sf::NonCopyable
{
 public:
  // Constructor of World class.
  explicit							World(sf::RenderWindow& window);
  // Controls world scrolling and entity movement per delta time.
  void								update(sf::Time dt);
  // Draw all drawable game objects in the current game world.
  void								draw();
  // Get the current command queue of the game.
  CommandQueue&						getCommandQueue();

 private:
  // Load all textures we need for the game world.
  void								loadTextures();
  // Build the whole game world(scene).
  void								buildScene();
  // Handle the case where the plane leaves the visible area of the screen.
  void								adaptPlayerPosition();
  // Check and fix diagonal movement situations.
  void								adaptPlayerVelocity();

 private:
  // We use enum to represent different layers.
  enum Layer
  {
    Background,
    Air,
    LayerCount
  };

 private:
  // Reference to the current sf::RenderWindow object.
  sf::RenderWindow&					mWindow;
  // A sf::View	object indicates current view.
  sf::View							mWorldView;
  // A TextureHolder object to hold all textures we need to build the game world.
  TextureHolder						mTextures;
  // A SceneNode object represents a scene.
  SceneNode							mSceneGraph;
  // Fixed-size(LayerCount indicates the size) static array to store pointers of each SceneNode.
  std::array<SceneNode*, LayerCount>	mSceneLayers;
  // A CommandQueue object which indicates the current command Queue.
  CommandQueue						mCommandQueue;

  // The bounding rectangle of the game world.
  sf::FloatRect						mWorldBounds;
  // The position where the player's plane appears in the beginning.
  sf::Vector2f						mSpawnPosition;
  // The speed with which the world is scrolled.
  float								mScrollSpeed;
  // A pointer to the player's aircraft.
  Aircraft*							mPlayerAircraft;
};

#endif // WORLD_HPP