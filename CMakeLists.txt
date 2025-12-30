cmake_minimum_required(VERSION 4.0)
project(AlienInvaders)

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

add_executable(AlienInvaders MACOSX_BUNDLE
        main.cpp
        src/Player.cpp
        src/Player.h
        src/Game.cpp
        src/Game.h
        src/Alien.cpp
        src/Alien.h
        src/Bullet.cpp
        src/Bullet.h
        src/MacBundlePaths.mm)


target_link_libraries(AlienInvaders PRIVATE raylib)

set(DIST_DIR "${CMAKE_SOURCE_DIR}/dist")

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

if(APPLE)
    target_link_libraries(AlienInvaders PRIVATE "-framework CoreFoundation")

    add_custom_command(TARGET AlienInvaders POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy_directory
            "${CMAKE_SOURCE_DIR}/Assets"
            "$<TARGET_BUNDLE_CONTENT_DIR:AlienInvaders>/Resources/Assets"
    )
endif()