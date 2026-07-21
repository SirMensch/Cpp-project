cmake_minimum_required(VERSION 3.21)
project(emulator-6502 CXX)

option(ENABLE_MASTER_DEBUG "Enable project-wide debug builds and verbose logging" ON)
if(ENABLE_MASTER_DEBUG)
    set(CMAKE_BUILD_TYPE "Debug" CACHE STRING "Choose the type of build" FORCE)
    message(STATUS ">> MASTER DEBUG ENABLED: Optimizations off, all logs compiled.")
else()
    set(CMAKE_BUILD_TYPE "Release" CACHE STRING "Choose the type of build" FORCE)
    message(STATUS ">> PRODUCTION MODE ENABLED: High optimizations, verbose logs stripped.")
endif()

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

find_package(SFML 3 COMPONENTS Graphics Window System REQUIRED)
find_package(spdlog CONFIG REQUIRED)

file(GLOB_RECURSE SRC_FILES "src/*.cpp")
add_executable(emulator-6502 ${SRC_FILES})

if(ENABLE_MASTER_DEBUG)
    target_compile_definitions(emulator-6502 PRIVATE 
        SPDLOG_ACTIVE_LEVEL=SPDLOG_LEVEL_TRACE
    )
else()
    target_compile_definitions(emulator-6502 PRIVATE 
        SPDLOG_ACTIVE_LEVEL=SPDLOG_LEVEL_INFO
    )
endif()

target_include_directories(emulator-6502 PRIVATE include)

target_link_libraries(emulator-6502 PRIVATE 
    SFML::Graphics 
    SFML::Window 
    SFML::System
    spdlog::spdlog
)