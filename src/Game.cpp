//
// Created by Jason Evans on 26/12/2025.
//

#include "Game.h"

Game::Game() {

}

void Game::Draw() const {
    player.Draw();

    for (auto* bullet : bullets) {
        bullet->Draw();
    }
}

void Game::Update(float deltaTime) {
    player.Update(deltaTime);

    if (IsKeyPressed(KEY_SPACE)) {
        bullets.push_back(new Bullet(player.posX, player.posY));
    }

    for (auto* bullet : bullets) {
        bullet->Update(deltaTime);
    }
}

Game::~Game() {

}
