// Include project header files
#include "Game.hpp"

// Include C++ standard headers.
#include <stdexcept>
#include <iostream>

// Main entrance of the program
int main() {
  // Try to launch the game.
  try {
    Game game;
    // Launch the program
    game.run();

  }
  // If fail, catch the exception.
  catch (std::exception& e)
  {
    // Output the exception message.
    std::cout << "\nEXCEPTION: " << e.what() << std::endl;
  }
  return 0;
}
