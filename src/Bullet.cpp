//
// Created by Jason Evans on 26/12/2025.
//

#include "Bullet.h"

Bullet::Bullet(float pX, float pY) {
    bulletTexture = LoadTexture("Assets/sprites.png");
    srcRect = {896.0, 256.0, 64, 64};
    destRect = {0, 0, 32, 32};
    origin = {0,0};
    speed = 300.0;
    isDead = false;
    posX = pX;
    posY = pY;
}

void Bullet::Draw() const {
    DrawTexturePro(bulletTexture, srcRect, destRect, origin, 0, WHITE);
}

void Bullet::Update(float deltaTime) {
    destRect.x = posX;
    destRect.y = posY;
    posY -= speed * deltaTime;
}

Bullet::~Bullet() {

}
