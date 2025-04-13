#include "BallObject.h"

BallObject::BallObject()
    : GameObject(), radius(12.5f), stuck(true) {
}

BallObject::BallObject(glm::vec2 pos, float radius, glm::vec2 velocity, Texture2D sprite)
    : GameObject(pos, glm::vec2(radius * 2.0f, radius * 2.0f), sprite, false, velocity, glm::vec3(1.0f)), radius(radius), stuck(true) {
}

glm::vec2 BallObject::move(float dt, unsigned int windowWidth, unsigned int windowHeight) {
    if (!this->stuck) {
        this->position += this->velocity * dt;

        if (this->position.x <= 0.0f) {
            this->velocity.x = -this->velocity.x;
            this->position.x = 0.0f;
        } else if (this->position.x + this->size.x >= windowWidth) {
            this->velocity.x = -this->velocity.x;
            this->position.x = windowWidth - this->size.x;
        }

        if (this->position.y <= 0.0f) {
            this->velocity.y = -this->velocity.y;
            this->position.y = 0.0f;
        }
        else if (this->position.y + this->size.y >= windowHeight) {
            this->velocity.y = -this->velocity.y;
            this->position.y = windowHeight - this->size.y;
        }
    }

    return this->position;
}

void BallObject::reset(glm::vec2 position, glm::vec2 velocity) {
    this->position = position;
    this->velocity = velocity;
    this->stuck = true;
}