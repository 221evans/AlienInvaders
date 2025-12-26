//
// Created by Jason Evans on 26/12/2025.
//

#ifndef TOYBOXJAM_GAME_H
#define TOYBOXJAM_GAME_H
#include <raylib.h>
#include <vector>

#include "Player.h"
#include "Bullet.h"

class Game {
public:
    Game();
    Player player;
    std::vector<Bullet*> bullets;
    void Draw() const;
    void Update(float deltaTime);
    Music themeSound;
    ~Game();
};


#endif //TOYBOXJAM_GAME_H