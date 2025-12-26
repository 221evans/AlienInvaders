//
// Created by Jason Evans on 26/12/2025.
//

#include "Player.h"

Player::Player() {
    posX = 50.0;
    posY = 400.0;
    srcRect = {768.0, 256.0, 64, 64};
    destRect = {posX, posY, 32, 32};
    playerTexture = LoadTexture("Assets/sprites.png");
    origin = {0,0};
    speed = 100.0;
}

void Player::Draw() const {
    DrawTexturePro(playerTexture, srcRect, destRect, origin, 0, WHITE);
}

void Player::Update(float deltaTime) {

    destRect.x = posX;
    destRect.y = posY;

    if (IsKeyDown(KEY_D)) {
        posX += speed * deltaTime;
    }
    if (IsKeyDown(KEY_A)) {
        posX -= speed * deltaTime;
    }
}

Player::~Player() {

}




