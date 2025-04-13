#include "../BallObject.h"
#include "../GameObject.h"

#include <vector>
#include <glad/glad.h>
#include <glm/glm.hpp>

enum Direction {
	UP,
	RIGHT,
	DOWN,
	LEFT
};

class CollisionHandler {
public:
	static bool checkCollision(BallObject*, GameObject*);
private:
	// Direction getDirection(glm::vec2 target);
};