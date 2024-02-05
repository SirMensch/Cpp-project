cmake_minimum_required(VERSION 3.25)
project(InversePendle)

set(CMAKE_CXX_STANDARD 20)

find_package(SFML 2.6.1 COMPONENTS graphics window REQUIRED)

include_directories(headers /usr/include libs/SFML)

add_executable(InversePendle src/main.cpp src/Simulator.cpp headers/Simulator.h src/Object.cpp headers/Object.h src/Stick.cpp
        headers/Stick.h headers/structs.h src/Platform.cpp headers/Platform.h src/InversePendulum.cpp headers/InversePendulum.h)

target_link_libraries(InversePendle PRIVATE sfml-graphics sfml-window)