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

# Resource files are copied next to the executable.
add_custom_command(
    TARGET shoot-the-aliens POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
        "${PROJECT_SOURCE_DIR}/ressources"
        "$<TARGET_FILE_DIR:shoot-the-aliens>/ressources"
)
