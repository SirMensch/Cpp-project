cmake_minimum_required(VERSION 3.21)
project(emulator-6502 CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

find_package(SFML 3 COMPONENTS Graphics Window System REQUIRED)

file(GLOB_RECURSE SRC_FILES "src/*.cpp")
add_executable(emulator-6502 ${SRC_FILES})

target_include_directories(emulator-6502 PRIVATE include)

target_link_libraries(emulator-6502 PRIVATE 
    SFML::Graphics 
    SFML::Window 
    SFML::System
)