//
// Created by Jason Evans on 26/12/2025.
//

#include "Game.h"

#include <algorithm>

#include "iostream"
Game::Game() {
    InitAudioDevice();
    themeSound = LoadMusicStream("Assets/titlebattle.wav");

    for (int row = 0; row < 5; row++) {
        for (int col = 0; col < 10; col++) {
            aliens.push_back(std::make_unique<Alien>(col * 40 + 50, row * 40 + 50));
        }
    }

    alienDirection = 1.0;
}

void Game::Draw() const {
    player.Draw();

    for (const auto& bullet : bullets) {
        bullet->Draw();
    }

    for (const auto& alien : aliens) {
        alien->Draw();
    }
}

void Game::Update(float deltaTime) {

    UpdateAlien(deltaTime);

    for (auto& bullet : bullets) {
        bullet->Update(deltaTime);
    }

    // Collision detection with bullet and alien
    for (auto& bullet : bullets) {
        for (auto& alien : aliens) {
            if (CheckCollisionRecs(bullet->destRect, alien->destRect)) {
                bullet->isDead = true;
                alien->isDead = true;
            }
        }
    }

    if (!IsMusicStreamPlaying(themeSound)) {
        PlayMusicStream(themeSound);
    }

    UpdateMusicStream(themeSound);

    player.Update(deltaTime);

    if (IsKeyPressed(KEY_SPACE)) {
        bullets.push_back(std::make_unique<Bullet>(player.posX, player.posY));
    }


    std::erase_if(bullets, [](const auto& bullet) {
        return bullet->isDead;
    });

    std::erase_if(aliens, [](const auto& alien) {
        return alien->isDead;
    });

    unsigned enemyCount = aliens.size();

    if (enemyCount == 0) {
        DrawText("You Win!", GetScreenWidth() / 2, GetScreenHeight() / 2, 40, RED);
    }
}


Game::~Game() {
    UnloadMusicStream(themeSound);
}

void Game::UpdateAlien(float deltaTime) {
    for (auto& alien : aliens) {
        alien->Update(deltaTime);
        alien->posX += alienDirection * alien->speed * deltaTime;
    }

    bool hitEdge = std::any_of(aliens.begin(), aliens.end(), [](const auto& alien) {
      return alien->posX <= 10 || alien->posX >= GetScreenWidth() - 40;
  });

    if (hitEdge) {
        alienDirection *= -1;
    }

}
