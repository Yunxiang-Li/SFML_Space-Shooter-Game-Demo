// Include project header files
#include "CommandQueue.hpp"
#include "SceneNode.hpp"

/**
 * Push a command into the back of the command queue.
 * @param command a Command object indicates a command we want to push to the back.
 */
void CommandQueue::push(const Command& command)
{
  mQueue.push(command);
}

/**
 * Pop a command from the first element of the command queue.
 * @return a Command object indicates the command we want to pop(front in the queue).
 */
Command CommandQueue::pop()
{
  Command command = mQueue.front();
  mQueue.pop();
  return command;
}

/**
 * Check if the command queue is empty or not.
 * @return a bool value indicates whether the command queue is empty or not.
 */
bool CommandQueue::isEmpty() const
{
  return mQueue.empty();
}