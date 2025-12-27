//
// Created by Jason Evans on 26/12/2025.
//

#ifndef TOYBOXJAM_PLAYER_H
#define TOYBOXJAM_PLAYER_H
#include <raylib.h>


class Player {
public:
    Player();
    float posX;
    float posY;
    int lives;
    bool isDead;
    Rectangle srcRect{};
    Rectangle destRect{};
    Texture2D playerTexture{};
    ~Player();

private:
    Vector2 origin{};
    float speed;

public:
    void Draw() const;
    void Update(float deltaTime);

};


#endif //TOYBOXJAM_PLAYER_H