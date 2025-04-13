#include "GameObject.h"

GameObject::GameObject() 
	: position(0.0f, 0.0f), size(1.0f, 1.0f), velocity(0.0f), color(1.0f), rotation(0.0f), sprite(), isSolid(false), isDestroyed(false) {}

GameObject::GameObject(glm::vec2 pos, glm::vec2 size, Texture2D sprite, bool isSolid, glm::vec2 velocity, glm::vec3 color)
	: position(pos), size(size), velocity(velocity), color(color), rotation(0.0f), sprite(sprite), isSolid(isSolid), isDestroyed(false) {}

void GameObject::draw(SpriteRenderer& renderer) {
	renderer.drawSprite(this->sprite, this->position, this->size, this->rotation, this->color);
}