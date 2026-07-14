cmake_minimum_required(VERSION 3.25)
project(InversePendle)

set(CMAKE_CXX_STANDARD 20)

# 1. Locate SFML 3 (vcpkg handles the magic behind the scenes)
find_package(SFML 3 COMPONENTS Graphics Window System REQUIRED)

# 2. Gather source files
file(GLOB_RECURSE SRC_FILES 
    "src/*.cpp"
)

add_executable(InversePendle ${SRC_FILES})

# 3. Modern Include Directories (Target-based)
# This replaces the old include_directories() line.
# It tells CMake where your local "headers" folder is, and 'PRIVATE' keeps it clean.
target_include_directories(InversePendle PRIVATE headers)

# 4. Link against modern SFML 3 targets
# SFML::Graphics automatically tells your compiler where the SFML headers are,
# so you don't need to specify them in include_directories at all.
target_link_libraries(InversePendle PRIVATE 
    SFML::Graphics 
    SFML::Window 
    SFML::System
)

# 5. Compiler Definitions
target_compile_definitions(InversePendle PRIVATE
    EXT_FORCE=1 
    DEBUG=1 
    C_SLIDING_MODE=0 
    C_PID=1 
    C_LQR=0
)