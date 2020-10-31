#ifndef LOADINGSTATE_HPP
#define LOADINGSTATE_HPP

// Include project header files
#include "State.hpp"

// Include our Third-Party SFML header
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/Text.hpp>

// Include C++ standard headers.
#include "ParallelTask.hpp"

/**
 * This class represents loading state which displays information of what is being loaded and a progress bar.
 */
class LoadingState : public State
{
 public:
  // Constructor of LoadingState class.
  LoadingState(StateStack& stack, Context context);

  void			        draw() override;
  bool			        update(sf::Time dt) override;
  bool			        handleEvent(const sf::Event& event) override;

  void					setCompletion(float percent);

 private:
  // a sf::Text object indicates the loading Resources string.
  sf::Text				mLoadingText;
  // a sf::RectangleShape for progress bar's background image.
  sf::RectangleShape	mProgressBarBackground;
  // a sf::RectangleShape for progress bar's image.
  sf::RectangleShape	mProgressBar;

  ParallelTask			mLoadingTask;
};

#endif // LOADINGSTATE_HPP