#ifndef GAME_H
#define GAME_H

#include <vector>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "GameLevel.h"
#include "BallObject.h"
#include "utility/CollisionHandler.h"

enum GameState {
    GAME_ACTIVE,
    GAME_MENU,
    GAME_WIN
};

class Game {
public:
    GameState state;
    bool keys[1024];
    unsigned int width, height;
    std::vector<GameLevel> levels;
    unsigned int level;

    Game(unsigned int width, unsigned int height);
    ~Game();

    void init();
    void processInput(float dt);
    void update(float dt);
    void render();
private:
    void doCollisions();
};

#endif
