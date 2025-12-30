#include <raylib.h>
#include "src/Game.h"

#ifdef __APPLE__
void SetMacAppWorkingDirectoryToResources();
#endif

int main() {

#ifdef __APPLE__
    SetMacAppWorkingDirectoryToResources();
#endif

    int windowWidth = 640;
    int windowHeight = 480;

    InitWindow(windowWidth, windowHeight, "Alien Invaders");

    Game game;

    SetTargetFPS(60);



    while (!WindowShouldClose()) {
        float deltaTime = GetFrameTime();

        // Update logic here
        game.Update(deltaTime);

        BeginDrawing();

        ClearBackground(BLACK);

        // Draw logic here
        game.Draw();


        EndDrawing();
    }

    CloseWindow();
}