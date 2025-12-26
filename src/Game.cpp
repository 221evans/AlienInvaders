//
// Created by Jason Evans on 26/12/2025.
//

#include "Game.h"
#include "iostream"
Game::Game() {
    InitAudioDevice();
    themeSound = LoadMusicStream("Assets/titlebattle.wav");
}

void Game::Draw() const {
    player.Draw();

    for (auto* bullet : bullets) {
        bullet->Draw();
    }
}

void Game::Update(float deltaTime) {


    if (!IsMusicStreamPlaying(themeSound)) {
        PlayMusicStream(themeSound);
    }

    UpdateMusicStream(themeSound);

    player.Update(deltaTime);

    if (IsKeyPressed(KEY_SPACE)) {
        bullets.push_back(new Bullet(player.posX, player.posY));
    }

    for (auto* bullet : bullets) {
        bullet->Update(deltaTime);
    }

    // Remove dead bullets
    std::erase_if(bullets,
                  [](const Bullet* bullet) {
                      if (bullet->isDead) {
                          delete bullet;  // Free memory
                          return true;    // Mark for removal
                      }
                      return false;
                  });

        std::cout << "bullet count" << bullets.size() << std::endl;
}

Game::~Game() {

}
