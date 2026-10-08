cmake_minimum_required(VERSION 3.12)

project(shoot-the-aliens)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

find_package(SFML 2.5.1 COMPONENTS
    system
    window
    graphics
    audio
    REQUIRED
)

file(GLOB SOURCES
    "${PROJECT_SOURCE_DIR}/src/*.cpp"
)

add_executable(shoot-the-aliens
    ${SOURCES}
)

target_include_directories(shoot-the-aliens
    PRIVATE
        "${PROJECT_SOURCE_DIR}/src"
)

target_link_libraries(shoot-the-aliens
    sfml-audio
    sfml-graphics
    sfml-window
    sfml-system
)

enable_testing()

# Standalone Test Target (No external dependencies needed)
add_executable(run_tests
    tests/test_main.cpp
    src/player.cpp
    src/explosion.cpp
    src/ship.cpp
    src/soundmanager.cpp
)

target_include_directories(run_tests
    PRIVATE
        "${PROJECT_SOURCE_DIR}/src"
)

target_link_libraries(run_tests
    PRIVATE
        sfml-audio
        sfml-graphics
        sfml-window
        sfml-system
)

# Register the executable directly with CTest
add_test(NAME AllTests COMMAND run_tests)
