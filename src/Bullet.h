//
// Created by Jason Evans on 26/12/2025.
//

#ifndef TOYBOXJAM_BULLET_H
#define TOYBOXJAM_BULLET_H
#include "raylib.h"


class Bullet {
public:
    Bullet(float posX, float posY, float dir);
    Texture2D bulletTexture{};
    Rectangle srcRect{};
    Rectangle destRect{};
    Vector2 origin{};
    float speed;
    float posX;
    float posY;
    float direction;
    bool isDead;



    void Draw() const;
    void Update(float deltaTime);



    ~Bullet();
};


#endif //TOYBOXJAM_BULLET_H