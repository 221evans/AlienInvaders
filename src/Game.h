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
    Player player;
    std::vector<std::unique_ptr<Bullet>> bullets;
    std::vector<std::unique_ptr<Alien>> aliens;
    void Draw() const;
    void Update(float deltaTime);
    Music themeSound;
    float alienDirection;
    ~Game();

private:
    void UpdateAlien(float deltaTime);

};


#endif //TOYBOXJAM_GAME_H