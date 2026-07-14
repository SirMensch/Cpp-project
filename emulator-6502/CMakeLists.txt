cmake_minimum_required(VERSION 3.21)
project(emulator-6502 CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

file(GLOB_RECURSE SRC_FILES 
    "src/*.cpp"
    "src/cpu/*.cpp"
)

add_executable(emulator-6502 src/main.cpp ${SRC_FILES})