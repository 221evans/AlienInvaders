//
// Created by Jason Evans on 26/12/2025.
//

#include "Alien.h"

Alien::Alien(float pX, float pY) {
    posX = pX;
    posY = pY;
    origin = {0,0};
    srcRect = {704.0,448.0, 64.0,64.0};
    destRect = {posX, posY, 32, 32};
    alienTexture = LoadTexture("Assets/sprites.png");
    speed = 50.0;
    isDead = false;
}

void Alien::Draw() const {
    DrawTexturePro(alienTexture, srcRect, destRect, origin, 0, WHITE);
}

void Alien::Update(float deltaTime) {
    destRect.x = posX;
    destRect.y = posY;
}

Alien::~Alien() {
    UnloadTexture(alienTexture);
}
