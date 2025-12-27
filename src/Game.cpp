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

    for (const auto& bullet : bullets) {
        bullet->Draw();
    }
}

void Game::Update(float deltaTime) {

    for (auto& bullet : bullets) {
        bullet->Update(deltaTime);
    }

    if (!IsMusicStreamPlaying(themeSound)) {
        PlayMusicStream(themeSound);
    }

    UpdateMusicStream(themeSound);

    player.Update(deltaTime);

    if (IsKeyPressed(KEY_SPACE)) {
        bullets.push_back(std::make_unique<Bullet>(player.posX, player.posY));
    }

    std::cout << "bullet count " << bullets.size() << std::endl;

    std::erase_if(bullets, [](const auto& bullet) {
        return bullet->isDead;
    });
}


Game::~Game() {

}
