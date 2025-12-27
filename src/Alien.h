//
// Created by Jason Evans on 26/12/2025.
//

#ifndef TOYBOXJAM_ALIEN_H
#define TOYBOXJAM_ALIEN_H
#include "raylib.h"


class Alien {
public:
    Alien(float pX, float pY);
    float posX;
    float posY;
    Rectangle srcRect{};
    Rectangle destRect{};
    Texture2D alienTexture{};
    float speed;
    bool isDead;
    ~Alien();

private:
    Vector2 origin{};


public:
    void Draw() const;
    void Update(float deltaTime);
};


#endif //TOYBOXJAM_ALIEN_H