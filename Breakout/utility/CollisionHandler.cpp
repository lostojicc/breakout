#include "CollisionHandler.h"

bool CollisionHandler::checkCollision(BallObject* ball, GameObject* box) {
	glm::vec2 center(ball->position + ball->radius);
	glm::vec2 aabbHalfExtents(box->size.x / 2.0f, box->size.y / 2.0f);
	glm::vec2 aabbCenter(box->position.x + aabbHalfExtents.x, box->position.y + aabbHalfExtents.y);

	glm::vec2 difference = center - aabbCenter;
	glm::vec2 clamped = glm::clamp(difference, -aabbHalfExtents, aabbHalfExtents);
	glm::vec2 closest = aabbCenter + clamped;

	difference = closest - center;
	return glm::length(difference) < ball->radius;
}