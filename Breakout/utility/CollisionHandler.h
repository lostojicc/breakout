#include "../BallObject.h"
#include "../GameObject.h"

#include <vector>
#include <tuple>
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
	static std::tuple<bool, Direction, glm::vec2> checkCollision(BallObject*, GameObject*);
private:
	static Direction getDirection(glm::vec2 target);
};