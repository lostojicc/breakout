#pragma once

#include <glad/glad.h>
#include <glm/glm.hpp>

#include "GameObject.h"
#include "utility/texture/Texture.h"

class BallObject : public GameObject {
public:
	float radius;
	bool stuck;

	BallObject();
	BallObject(glm::vec2 pos, float radius, glm::vec2 velocity, Texture2D sprite);

	glm::vec2 move(float dt, unsigned int windowWidth);
	void reset(glm::vec2 position, glm::vec2 velocity);
};

