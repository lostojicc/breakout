#ifndef GAMELEVEL_H
#define GAMELEVEL_H

#include <vector>
#include <string>
#include <fstream>
#include <sstream>

#include <glad/glad.h>
#include <glm/glm.hpp>

#include "gameobject.h"
#include "utility/spriterenderer.h"
#include "utility/resourcemanager.h"

class GameLevel {
public:
    std::vector<GameObject> bricks;
 
    GameLevel() {}

    void load(const char* file, unsigned int levelWidth, unsigned int levelHeight);
    void draw(SpriteRenderer& renderer);
    bool isCompleted();
private:
    void init(std::vector<std::vector<unsigned int>> tileData, unsigned int levelWidth, unsigned int levelHeight);
};

#endif