cmake_minimum_required(VERSION 3.25)
project(InversePendle)

set(CMAKE_CXX_STANDARD 20)

find_package(SFML 2.6.1 COMPONENTS graphics window REQUIRED)
find_package(Boost REQUIRED COMPONENTS filesystem)

include_directories(headers /usr/include libs/SFML ${Boost_INCLUDE_DIRS})

add_executable(InversePendle src/main.cpp src/Simulator.cpp headers/Simulator.h src/Object.cpp headers/Object.h src/Stick.cpp
        headers/Stick.h headers/structs.h src/Platform.cpp headers/Platform.h src/InversePendulum.cpp headers/InversePendulum.h headers/Config.h headers/EventHandler.h src/Controller.cpp headers/Controller.h src/SlidingMode.cpp headers/SlidingMode.h)

target_link_libraries(InversePendle PRIVATE sfml-graphics sfml-window ${Boost_LIBRARIES})

add_compile_definitions(EXT_FORCE=1; DEBUG=1; SLIDING_MODE=1)