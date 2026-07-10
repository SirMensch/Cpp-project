cmake_minimum_required(VERSION 3.21)
project(MotionPlanningSandbox CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
enable_testing()

# Silence deprecation warnings from older third-party subdirectories
cmake_policy(SET CMP0048 NEW) 
set(CMAKE_WARN_DEPRECATED OFF CACHE BOOL "" FORCE)

# -----------------------------------------------------------------------------
# Dependencies via vcpkg
# -----------------------------------------------------------------------------
find_package(Eigen3 REQUIRED)
find_package(fcl REQUIRED)
find_package(Catch2 REQUIRED)

# -----------------------------------------------------------------------------
# Polyscope via FetchContent (Lightweight 3D Frontend UI)
# -----------------------------------------------------------------------------
include(FetchContent)
FetchContent_Declare(
    polyscope
    GIT_REPOSITORY https://github.com/nmwsharp/polyscope.git
    GIT_TAG        v2.3.0
)
FetchContent_MakeAvailable(polyscope)

# -----------------------------------------------------------------------------
# Source & Test File Discovery
# -----------------------------------------------------------------------------
# 1. Gather all production code (.cpp files) inside src/ EXCEPT main.cpp
file(GLOB_RECURSE SRC_FILES 
    "src/simulation/*.cpp"
    "src/planners/*.cpp"
    "src/visualization/*.cpp"
    "src/planners/*.cpp"
)

# 2. Gather all test files
file(GLOB_RECURSE TEST_FILES "tests/*.cpp")

# -----------------------------------------------------------------------------
# Executable Targets
# -----------------------------------------------------------------------------
# Both apps need your production SRC_FILES to function!
add_executable(sim_app src/main.cpp ${SRC_FILES})
add_executable(run_tests ${TEST_FILES} ${SRC_FILES})

# -----------------------------------------------------------------------------
# Include Directories & Target Linking
# -----------------------------------------------------------------------------
# Setup for your Main App
target_include_directories(sim_app PRIVATE src)
target_link_libraries(sim_app PRIVATE
    Eigen3::Eigen
    fcl
    polyscope     # Crucial for headers!
)

# Setup for your Test Runner
target_include_directories(run_tests PRIVATE src)
target_link_libraries(run_tests PRIVATE
    Catch2::Catch2WithMain
    Eigen3::Eigen
    fcl
    polyscope     # 💡 ADD THIS LINE HERE TOO!
)

# -----------------------------------------------------------------------------
# Test Registration
# -----------------------------------------------------------------------------
add_test(NAME AllTests COMMAND run_tests)