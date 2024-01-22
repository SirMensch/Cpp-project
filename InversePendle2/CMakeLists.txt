cmake_minimum_required(VERSION 3.25)
project(InversePendle)

set(CMAKE_CXX_STANDARD 20)

find_package(SFML 2.6.1 COMPONENTS graphics window REQUIRED)

include_directories(headers /usr/include h:/C++-Libraries/SFML-2.6.1/include)

add_executable(InversePendle main.cpp Simulator.cpp Simulator.h Objects.cpp Objects.h)

target_link_libraries(InversePendle PRIVATE sfml-graphics sfml-window)