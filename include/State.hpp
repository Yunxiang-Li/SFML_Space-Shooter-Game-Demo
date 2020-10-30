#ifndef STATE_HPP
#define STATE_HPP

// Include project header files
#include "StateIdentifiers.hpp"
#include "ResourceIdentifiers.hpp"

// Include our Third-Party SFML header
#include <SFML/System/Time.hpp>
#include <SFML/Window/Event.hpp>

// Include C++ standard headers.
#include <memory>

// Forward declaration of sf::RenderWindow class.
namespace sf
{
  class RenderWindow;
}

// Forward declaration of StateStack and Player class.
class StateStack;
class Player;

/**
 * This virtual class represents all behaviour of a general game state.
 */
class State
{
 public:
  // Using Ptr as an alias of std::unique_ptr<State>.
  typedef std::unique_ptr<State> Ptr;

  // A struct indicates a holder of shared objects between all states of the game.
  struct Context
  {
    Context(sf::RenderWindow& window, TextureHolder& textures, FontHolder& fonts, Player& player);

    sf::RenderWindow*	window;
    TextureHolder*		textures;
    FontHolder*			fonts;
    Player*				player;
  };

 public:
  // Constructor of the State class.
  State(StateStack& stack, Context context);
  // Virtual destructor.
  virtual			~State();
  // Virtual draw method.
  virtual void		draw() = 0;
  // Virtual update method.
  virtual bool		update(sf::Time dt) = 0;
  // Virtual handleEvent method.
  virtual bool		handleEvent(const sf::Event& event) = 0;

 protected:
  // Push current state to the game state stack.
  void				requestStackPush(States::ID stateID);
  // Pop current state from the game state stack.
  void				requestStackPop();
  // Clear the game state stack.
  void				requestStateClear();
  // Get current state object's Context member.
  Context			getContext() const;


 private:
  // A pointer to the StateStack object indicates the game state stack.
  StateStack*			mStack;
  // A struct indicates a holder of shared objects between all states of the game.
  Context				mContext;
};

#endif // STATE_HPP