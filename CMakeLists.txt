cmake_minimum_required(VERSION 3.16)

project(shoot-the-aliens)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

include(FetchContent)

FetchContent_Declare(
    SFML
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG 2.6.2
)

FetchContent_MakeAvailable(SFML)

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
add_executable(unit_tests
    tests/test_main.cpp
    src/alien.cpp
    src/player.cpp
    src/explosion.cpp
    src/projectile.cpp
    src/ship.cpp
    src/soundmanager.cpp
)

target_include_directories(unit_tests
    PRIVATE
        "${PROJECT_SOURCE_DIR}/src"
)

target_link_libraries(unit_tests
    PRIVATE
        sfml-audio
        sfml-graphics
        sfml-window
        sfml-system
)

# Register the executable directly with CTest
add_test(NAME AllTests COMMAND unit_tests)


if(WIN32)
    # Select the correct OpenAL DLL for the architecture
    if(CMAKE_SIZEOF_VOID_P EQUAL 8)
        set(OPENAL_ARCH "x64")
    else()
        set(OPENAL_ARCH "x86")
    endif()

    set(OPENAL_DLL
        "${sfml_SOURCE_DIR}/extlibs/bin/${OPENAL_ARCH}/openal32.dll"
    )

    # Copy required DLLs for the game
    add_custom_command(TARGET shoot-the-aliens POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
            $<TARGET_FILE:sfml-system>
            $<TARGET_FILE:sfml-window>
            $<TARGET_FILE:sfml-graphics>
            $<TARGET_FILE:sfml-audio>
            "${OPENAL_DLL}"
            $<TARGET_FILE_DIR:shoot-the-aliens>
    )

    # Copy required DLLs for the tests
    add_custom_command(TARGET unit_tests POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
            $<TARGET_FILE:sfml-system>
            $<TARGET_FILE:sfml-window>
            $<TARGET_FILE:sfml-graphics>
            $<TARGET_FILE:sfml-audio>
            "${OPENAL_DLL}"
            $<TARGET_FILE_DIR:unit_tests>
    )
endif()