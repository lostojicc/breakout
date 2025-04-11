#include "Game.h"
#include "utility/ResourceManager.h"
#include "utility/SpriteRenderer.h"

SpriteRenderer* renderer;

Game::Game(unsigned int width, unsigned int height)
    : state(GAME_ACTIVE), keys(), width(width), height(height) {
}

Game::~Game() {
    delete renderer;
}

void Game::init() {
    ResourceManager::loadShader("shader/sprite.vert", "shader/sprite.frag", nullptr, "sprite");
    glm::mat4 projection = glm::ortho(0.0f, static_cast<float>(this->width), static_cast<float>(this->height), 0.0f, -1.0f, 1.0f);
    ResourceManager::getShader("sprite").Use().SetInteger("image", 0);
    ResourceManager::getShader("sprite").SetMatrix4("projection", projection);
    renderer = new SpriteRenderer(ResourceManager::getShader("sprite"));
    ResourceManager::loadTexture("texture/cartoon-guy.png", true, "guy");
}

void Game::update(float dt) {}

void Game::processInput(float dt) {}

void Game::render() {
    renderer->drawSprite(ResourceManager::getTexture("guy"), glm::vec2(250.0f, 100.0f), glm::vec2(300.0f, 400.0f), 0.0f, glm::vec3(1.0f, 1.0f, 1.0f));
}