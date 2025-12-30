Alien Invaders

Alien Invaders is a Space Invaders style arcade shooter created for the Toy Box Game Jam.

The game is a small homage to classic fixed-screen arcade shooters, built using the official assets provided by the Toy Box Game Jam.
Gameplay

Classic arcade shooter inspired by Space Invaders

Tech Stack

Language: C++

Framework: raylib

Build System: CMake

Platforms: Windows, macOS

Assets

All visual and audio assets used in this project were provided by the Toy Box Game Jam and are used in accordance with the jam’s rules.

No third-party assets outside of the jam asset pack were used.

Building from Source
Requirements

CMake 3.20+

C++ compiler

Windows: MinGW-w64 or MSVC

macOS: Xcode Command Line Tools

Internet connection (raylib is fetched automatically via CMake)

Build Instructions
macOS
mkdir build
cd build
cmake ..
cmake --build .


This will generate a native macOS application bundle in the build directory.

Windows (MinGW example)
mkdir build
cd build
cmake -G "MinGW Makefiles" ..
cmake --build .


The executable and required runtime files will be generated in the build output.

Controls

A / D – Move

Space – Shoot

Esc – Quit

Game Jam Info

Jam: Toy Box Game Jam

Assets: Jam-provided asset pack only

License

This project was created for a game jam and is shared for educational and portfolio purposes.
