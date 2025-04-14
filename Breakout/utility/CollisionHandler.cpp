#include "CollisionHandler.h"

std::tuple<bool, Direction, glm::vec2> CollisionHandler::checkCollision(BallObject* ball, GameObject* box) {
	glm::vec2 center(ball->position + ball->radius);
	glm::vec2 aabbHalfExtents(box->size.x / 2.0f, box->size.y / 2.0f);
	glm::vec2 aabbCenter(box->position.x + aabbHalfExtents.x, box->position.y + aabbHalfExtents.y);

	glm::vec2 difference = center - aabbCenter;
	glm::vec2 clamped = glm::clamp(difference, -aabbHalfExtents, aabbHalfExtents);
	glm::vec2 closest = aabbCenter + clamped;

	difference = closest - center;
	return (glm::length(difference) <= ball->radius) ? std::make_tuple(true, getDirection(difference), difference) : std::make_tuple(false, (Direction)0, glm::vec2(0.0f, 0.0f));
}

Direction CollisionHandler::getDirection(glm::vec2 target) {
	glm::vec2 compass[] = {
		glm::vec2(0.0f, 1.0f),
		glm::vec2(1.0f, 0.0f),
		glm::vec2(0.0f, -1.0f),
		glm::vec2(-1.0f, 0.0f)
	};

	float max = 0.0f;
	unsigned int best_match = -1;

	for (unsigned int i = 0; i < 4; i++) {
		float dotProduct = glm::dot(glm::normalize(target), compass[i]);
		if (dotProduct > max) {
			max = dotProduct;
			best_match = i;
		}
	}

	return (Direction)best_match;
}