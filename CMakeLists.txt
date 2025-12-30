cmake_minimum_required(VERSION 3.20)
project(AlienInvaders)

set(CMAKE_CXX_STANDARD 26)

include(FetchContent)

# ---- raylib options MUST be set before FetchContent_MakeAvailable(raylib) ----
if (EMSCRIPTEN)
    # Tell raylib to build for the web platform
    set(PLATFORM "Web" CACHE STRING "" FORCE)

    # Optional: raylib will use Emscripten's GLFW implementation when PLATFORM=Web,
    # so we generally don't want/need external GLFW/X11 detection.
    set(USE_EXTERNAL_GLFW OFF CACHE BOOL "" FORCE)
endif()

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

# ---- Sources ----
set(SOURCES
        main.cpp
        src/Player.cpp
        src/Game.cpp
        src/Alien.cpp
        src/Bullet.cpp
)

set(HEADERS
        src/Player.h
        src/Game.h
        src/Alien.h
        src/Bullet.h
)

# Only compile Objective-C++ file on Apple
if(APPLE)
    list(APPEND SOURCES src/MacBundlePaths.mm)
endif()

add_executable(AlienInvaders
        ${SOURCES}
        ${HEADERS}
)

target_link_libraries(AlienInvaders PRIVATE raylib)

set(DIST_DIR "${CMAKE_SOURCE_DIR}/dist")

# ---- Windows (MinGW) packaging ----
if (WIN32 AND MINGW)
    get_filename_component(MINGW_BIN_DIR "${CMAKE_CXX_COMPILER}" DIRECTORY)

    add_custom_command(TARGET AlienInvaders POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E rm -rf "${DIST_DIR}"
            COMMAND ${CMAKE_COMMAND} -E make_directory "${DIST_DIR}"
            COMMAND ${CMAKE_COMMAND} -E copy "$<TARGET_FILE:AlienInvaders>" "${DIST_DIR}"
            COMMAND ${CMAKE_COMMAND} -E copy_directory "${CMAKE_SOURCE_DIR}/Assets" "${DIST_DIR}/Assets"
    )

    foreach(dll IN ITEMS libwinpthread-1.dll libstdc++-6.dll libgcc_s_seh-1.dll)
        add_custom_command(TARGET AlienInvaders POST_BUILD
                COMMAND ${CMAKE_COMMAND} -E copy_if_different
                "${MINGW_BIN_DIR}/${dll}"
                "${DIST_DIR}"
        )
    endforeach()
endif()

# ---- macOS bundle assets ----
if(APPLE)
    set_target_properties(AlienInvaders PROPERTIES MACOSX_BUNDLE TRUE)
    target_link_libraries(AlienInvaders PRIVATE "-framework CoreFoundation")

    add_custom_command(TARGET AlienInvaders POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy_directory
            "${CMAKE_SOURCE_DIR}/Assets"
            "$<TARGET_BUNDLE_CONTENT_DIR:AlienInvaders>/Resources/Assets"
    )
endif()

# ---- Web build flags ----
if (EMSCRIPTEN)
    set_target_properties(AlienInvaders PROPERTIES SUFFIX ".html")

    target_link_options(AlienInvaders PRIVATE
            -sUSE_GLFW=3
            -sASYNCIFY
            -sALLOW_MEMORY_GROWTH=1
            "--preload-file" "${CMAKE_SOURCE_DIR}/Assets@Assets"
    )
endif()
