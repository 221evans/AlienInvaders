cmake_minimum_required(VERSION 4.0)
project(ToyBoxJam)

set(CMAKE_CXX_STANDARD 26)

include(FetchContent)
FetchContent_Declare(
        raylib
        GIT_REPOSITORY https://github.com/raysan5/raylib.git
        GIT_TAG 5.5
)
FetchContent_Declare(
        raygui
        GIT_REPOSITORY https://github.com/raysan5/raygui.git
        GIT_TAG 4.0
)
FetchContent_MakeAvailable(raylib)
FetchContent_MakeAvailable(raygui)

add_executable(ToyBoxJam main.cpp
        src/Player.cpp
        src/Player.h
        src/Game.cpp
        src/Game.h
        src/Alien.cpp
        src/Alien.h
        src/Bullet.cpp
        src/Bullet.h)

# Copy Assets folder to build directory
add_custom_command(TARGET ToyBoxJam POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_SOURCE_DIR}/Assets
        $<TARGET_FILE_DIR:ToyBoxJam>/Assets)



target_link_libraries(ToyBoxJam PRIVATE raylib)

# For Windows, copy raylib DLL to build directory
if(WIN32)
    add_custom_command(TARGET ToyBoxJam POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy_if_different
            $<TARGET_FILE:raylib>
            $<TARGET_FILE_DIR:ToyBoxJam>
    )
endif()
