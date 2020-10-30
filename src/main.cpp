// Include project header files
#include "Game.hpp"
#include "Application.hpp"

// Include C++ standard headers.
#include <stdexcept>
#include <iostream>

// Main entrance of the program
int main() {
  // Try to launch the game.
  try {
    Application app;
    app.run();

  }
  // If fail, catch the exception.
  catch (std::exception& e)
  {
    // Output the exception message.
    std::cout << "\nEXCEPTION: " << e.what() << std::endl;
  }
  return 0;
}
