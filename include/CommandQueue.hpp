#ifndef COMMANDQUEUE_HPP
#define COMMANDQUEUE_HPP

// Include project header files
#include "Command.hpp"

// Include C++ standard headers.
#include <queue>

/**
 * This class represents a queue of Command objects.
 */
class CommandQueue
{
 public:
  // Push one command into the CommandQueue object.
  void						push(const Command& command);
  // Pop one command from the CommandQueue object.
  Command					pop();
  // Check if the CommandQueue is empty or not.
  bool						isEmpty() const;

 private:
  // A std::queue<Command> object which stores all commands by a queue.
  std::queue<Command>		mQueue;
};

#endif // COMMANDQUEUE_HPP