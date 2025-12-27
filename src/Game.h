//
// Created by Jason Evans on 26/12/2025.
//

#ifndef TOYBOXJAM_GAME_H
#define TOYBOXJAM_GAME_H

#include <memory>
#include <raylib.h>
#include <vector>

#include "Alien.h"
#include "Player.h"
#include "Bullet.h"

class Game {
public:
    Game();
    std::vector<std::unique_ptr<Player>> newPlayer;
    std::vector<std::unique_ptr<Bullet>> playerBullets;
    std::vector<std::unique_ptr<Bullet>> alienBullets;
    std::vector<std::unique_ptr<Alien>> aliens;
    void Draw() const;
    void Update(float deltaTime);
    Music themeSound;
    float alienDirection;
    ~Game();

private:
    void UpdateAlien(float deltaTime);
    float alienShootTime;
    float alienShootDelay;
};


#endif //TOYBOXJAM_GAME_H