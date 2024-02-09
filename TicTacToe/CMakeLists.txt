cmake_minimum_required(VERSION 3.17)
project(TicTacToe)

set(CMAKE_CXX_STANDARD 17)

# Find SFML components
find_package(SFML 2.6.1 COMPONENTS graphics window system REQUIRED)

# Include directories for SFML
include_directories(${SFML_INCLUDE_DIRS})

# Add the executable
add_executable(TicTacToe main.cpp)

# Link SFML libraries to the executable
target_link_libraries(TicTacToe PRIVATE sfml-graphics sfml-window sfml-system sfml-audio)
target_link_libraries(TicTacToe ${SFML_LIBRARIES} ${SFML_DEPENDENCIES})

