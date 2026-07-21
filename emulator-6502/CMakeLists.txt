cmake_minimum_required(VERSION 3.21)
project(emulator-6502 CXX)

# Debug vs Release
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

# Externals
find_package(SFML 3 COMPONENTS Graphics Window System REQUIRED)
find_package(spdlog CONFIG REQUIRED)
include(FetchContent)
FetchContent_Declare(
    googletest
    URL https://github.com/google/googletest/archive/refs/heads/main.zip
)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

file(GLOB_RECURSE SRC_FILES "src/*.cpp")
add_executable(emulator-6502 ${SRC_FILES})

target_include_directories(emulator-6502 PRIVATE include)

target_link_libraries(emulator-6502 PRIVATE 
    SFML::Graphics 
    SFML::Window 
    SFML::System
    spdlog::spdlog
)

# Logs
if(ENABLE_MASTER_DEBUG)
    target_compile_definitions(emulator-6502 PRIVATE 
        SPDLOG_ACTIVE_LEVEL=SPDLOG_LEVEL_TRACE
    )    
else()    
    target_compile_definitions(emulator-6502 PRIVATE 
        SPDLOG_ACTIVE_LEVEL=SPDLOG_LEVEL_INFO
    )    
endif()    

# -----------------------------------------------------------

# Tests 
file(GLOB_RECURSE CORE_FILES "src/*.cpp")
list(FILTER CORE_FILES EXCLUDE REGEX "main\\.cpp")

file(GLOB ROM_FILES "${CMAKE_CURRENT_SOURCE_DIR}/tests/roms/timendus/bin/*.ch8")

add_executable(emulator-6502-tests
    tests/test_timendus.cpp
    ${CORE_FILES}
)

target_include_directories(emulator-6502-tests PRIVATE include)

# Point the test executable to your submodule ROM directory
target_compile_definitions(emulator-6502-tests PRIVATE 
    ROM_DIR="${CMAKE_CURRENT_SOURCE_DIR}/tests/roms/timendus/bin"
    SOL_DIR="${CMAKE_CURRENT_SOURCE_DIR}/tests/solutions"
    SPDLOG_ACTIVE_LEVEL=SPDLOG_LEVEL_TRACE
)

# Link Google Test, dependencies, and testing tools
target_link_libraries(emulator-6502-tests PRIVATE 
    GTest::gtest_main
    SFML::Graphics 
    SFML::Window 
    SFML::System
    spdlog::spdlog
)

include(GoogleTest)
gtest_discover_tests(emulator-6502-tests)


