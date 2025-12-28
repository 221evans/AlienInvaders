//
// Created by Jason Evans on 26/12/2025.
//

#include "Game.h"
#include <algorithm>
#include "iostream"

#define RAYGUI_IMPLEMENTATION
#include "../raygui.h"

Game::Game() {
    InitAudioDevice();
    themeSound = LoadMusicStream("Assets/titlebattle.wav");
    hitSound = LoadSound("Assets/hit.wav");
    shootSound = LoadSound("Assets/shoot.wav");
    alienDirection = 1.0f;
    alienShootTime = 0.0f;
    alienShootDelay = 1.0f;
    playerShootTimer = 0.0f;
    playerShootDelay = 1.0f;
    canPlayerShoot = true;
    game_state = MENU;


    for (int row = 0; row < 5; row++) {
        for (int col = 0; col < 10; col++) {
            aliens.push_back(std::make_unique<Alien>(col * 40 + 50, row * 40 + 50));
        }
    }

    newPlayer.push_back(std::make_unique<Player>());
}

void Game::Draw() {

    if (game_state == MENU) {
        if (GuiButton(Rectangle{GetScreenWidth() / 2.0f - 100, 200, 120, 40}, "Start Game")) {
            game_state = PLAYING;
        }
    }

    if (game_state == PLAYING) {
        for (const auto& player : newPlayer) {
            player->Draw();
        }

        for (const auto& bullet : playerBullets) {
            bullet->Draw(WHITE);
        }

        for (const auto& bullet : alienBullets) {
            bullet->Draw(RED);
        }

        for (const auto& alien : aliens) {
            alien->Draw();
        }
    }

    if (game_state == GAMEOVER) {
        DrawText("Game Over", GetScreenWidth() / 2 -120, GetScreenHeight() / 2 - 100, 40, RED);
        PlayAgain();
    }
    if (game_state == GAMEWIN) {
        DrawText("You Win!", GetScreenWidth() / 2, GetScreenHeight() / 2, 40, RED);
        PlayAgain();
    }
}

void Game::Update(float deltaTime) {

    if (game_state == MENU) {

    }

    if (game_state == PLAYING) {

        UpdateAlien(deltaTime);

        alienShootTime += deltaTime;
        if (alienShootTime >= alienShootDelay) {
            alienShootTime = 0.0f;

            if (!aliens.empty()) {
                int randomIndex = GetRandomValue(0, static_cast<int>(aliens.size() - 1));
                alienBullets.push_back(std::make_unique<Bullet>(
                    aliens[randomIndex]->posX,
                    aliens[randomIndex]->posY,
                    1.0f
                    ));
            }

        }

        for (const auto& player : newPlayer) {
            DrawText(("Player Lives: " + std::to_string(player->lives)).c_str(), 10, 10, 20, RED );
            player->Update(deltaTime);

            if (IsKeyPressed(KEY_SPACE) && canPlayerShoot) {

                playerBullets.push_back(std::make_unique<Bullet>(player->posX, player->posY, -1.0f));
                PlaySound(shootSound);
                canPlayerShoot = false;
            }

            // player shoot timer
            if (!canPlayerShoot) {

                playerShootTimer += deltaTime;

                if (playerShootTimer >= playerShootDelay) {
                    canPlayerShoot = true;
                    playerShootTimer = 0.0f;
                }
            }

            if (player->lives <= 0) {
                player->isDead = true;
            }
        }

        for (auto& bullet : playerBullets) {
            bullet->Update(deltaTime);
        }

        for (auto& bullet : alienBullets) {
            bullet->Update(deltaTime);
        }

        HandleCollision();

        if (newPlayer.empty()) {
            game_state = GAMEOVER;
            newPlayer.clear();
            newPlayer.push_back(std::make_unique<Player>());

            aliens.clear();
            for (int row = 0; row < 5; row++) {
                for (int col = 0; col < 10; col++) {
                    aliens.push_back(std::make_unique<Alien>(col * 40 + 50, row * 40 + 50));
                }
            }

            alienBullets.clear();
            playerBullets.clear();
        }


        if (!IsMusicStreamPlaying(themeSound)) {
            PlayMusicStream(themeSound);
        }


        UpdateMusicStream(themeSound);
        HandleDeletion();

        unsigned enemyCount = aliens.size();

        if (enemyCount == 0) {
            DrawText("You Win!", GetScreenWidth() / 2, GetScreenHeight() / 2, 40, RED);
            game_state = GAMEWIN;
            aliens.clear();
            for (int row = 0; row < 5; row++) {
                for (int col = 0; col < 10; col++) {
                    aliens.push_back(std::make_unique<Alien>(col * 40 + 50, row * 40 + 50));
                }
            }

            alienBullets.clear();
            playerBullets.clear();
        }

        std::cout << "Bullet count " << alienBullets.size() << std::endl;
    }

    else if (game_state == GAMEOVER) {

    }

}

void Game::UpdateAlien(float deltaTime) {
    for (auto& alien : aliens) {
        alien->Update(deltaTime);
        alien->posX += alienDirection * alien->speed * deltaTime;
    }

    const bool hitEdge = std::ranges::any_of(aliens, [](const auto& alien) {
      return alien->posX <= 10 || alien->posX >= GetScreenWidth() - 40;
  });

    if (hitEdge) {
        alienDirection *= -1;
    }

}

void Game::HandleDeletion() {

    std::erase_if(playerBullets, [](const auto& bullet) {
      return bullet->isDead;
  });

    std::erase_if(alienBullets, [](const auto& bullet) {
        return bullet->isDead;
    });

    std::erase_if(aliens, [](const auto& alien) {
        return alien->isDead;
    });

    std::erase_if(newPlayer, [](const auto& player) {
        return player->isDead;
    });
}

void Game::HandleCollision() const {

    // Collision detection with bullet and alien
    for (auto& bullet : playerBullets) {
        for (auto& alien : aliens) {
            if (CheckCollisionRecs(bullet->destRect, alien->destRect)) {
                bullet->isDead = true;
                alien->isDead = true;
                PlaySound(hitSound);
            }
        }
    }

    // Collision detection with alien bullets and player
    for (auto& bullet : alienBullets) {

        for (auto& player : newPlayer) {
            if (CheckCollisionRecs(bullet->destRect, player->destRect)) {
                bullet->isDead = true;
                player->lives -= 1;
                PlaySound(hitSound);
            }
        }
    }
}

void Game::PlayAgain() {
    if (GuiButton(Rectangle{GetScreenWidth() / 2.0f - 60, 200, 120, 40}, "Play Again")) {
        game_state = PLAYING;
    }
}

Game::~Game() {
    UnloadMusicStream(themeSound);
    UnloadSound(hitSound);
    UnloadSound(shootSound);
}
