
# This CMakeLists.txt works for CLion under Windows 10 OS.

# Set up the minimum version of cmake
cmake_minimum_required(VERSION 3.15)

# Set the project name
project(SFML_Space-Shooter-Game)

# Link SFML libraries statically
set(SFML_STATIC_LIBRARIES TRUE)

# Set the C++ standard to be used
set(CMAKE_CXX_STANDARD 11)

# Include header files folder
include_directories(include/)

# Set cmake warning.
set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra")

# Set the path to SFML library
set(SFML_DIR "D:/SFML/lib/cmake/SFML")

# look for SFML package and add it
find_package(SFML REQUIRED COMPONENTS audio network graphics window system)

# Set output directory to the bin folder
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})

# Add the executable of the program
add_executable(SpaceShooterGame src/main.cpp
               src/Game.cpp src/Entity.cpp src/Aircraft.cpp src/SceneNode.cpp
               src/SpriteNode.cpp src/World.cpp src/Command.cpp src/Player.cpp
               src/CommandQueue.cpp)

# Set linked libraries
target_link_libraries(SpaceShooterGame PUBLIC sfml-system sfml-window sfml-graphics sfml-network sfml-audio)
