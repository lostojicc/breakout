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

const glm::vec2 PLAYER_SIZE(100.0f, 20.0f);
const float PLAYER_VELOCITY(500.0f);

const float BALL_RADIUS = 12.5f;
const glm::vec2 INITIAL_BALL_VELOCITY(100.0f, -350.0f);

GameObject* player;
BallObject* ball;

void Game::init() {
    ResourceManager::loadShader("shader/sprite.vert", "shader/sprite.frag", nullptr, "sprite");
    glm::mat4 projection = glm::ortho(0.0f, static_cast<float>(this->width),
        static_cast<float>(this->height), 0.0f, -1.0f, 1.0f);
    ResourceManager::getShader("sprite").Use().SetInteger("image", 0);
    ResourceManager::getShader("sprite").SetMatrix4("projection", projection);
    renderer = new SpriteRenderer(ResourceManager::getShader("sprite"));

    ResourceManager::loadTexture("texture/background.jpg", false, "background");
    ResourceManager::loadTexture("texture/block.png", false, "block");
    ResourceManager::loadTexture("texture/block_solid.png", false, "block_solid");
    ResourceManager::loadTexture("texture/paddle.png", false, "paddle");
    ResourceManager::loadTexture("texture/ball.png", true, "ball");

    glm::vec2 playerPos = glm::vec2(
        this->width / 2.0f - PLAYER_SIZE.x / 2.0f,
        this->height - PLAYER_SIZE.y
    );
    player = new GameObject(playerPos, PLAYER_SIZE, ResourceManager::getTexture("paddle"), false);

    GameLevel one;
    one.load("level/bubi.lvl", this->width, this->height / 2);
    this->levels.push_back(one);
    GameLevel two;
    two.load("level/space-invaders.lvl", this->width, this->height / 2);
    this->levels.push_back(two);
    this->level = 0;

    glm::vec2 ballPos = playerPos + glm::vec2(PLAYER_SIZE.x / 2.0f - BALL_RADIUS, -BALL_RADIUS * 2.0f);
    ball = new BallObject(ballPos, BALL_RADIUS, INITIAL_BALL_VELOCITY, ResourceManager::getTexture("ball"));
}

void Game::update(float dt) {
    ball->move(dt, this->width, this->height);
    doCollisions();
}

void Game::doCollisions() {
    for (GameObject& brick : this->levels[this->level].bricks) {
        if (brick.isDestroyed)
            continue;

        if (CollisionHandler::checkCollision(ball, &brick)) {
            if (!brick.isSolid)
                brick.isDestroyed = true;
        }
    }
}

void Game::processInput(float dt) {
    if (this->state == GAME_ACTIVE) {
        float velocity = PLAYER_VELOCITY * dt;
        // move playerboard
        if (this->keys[GLFW_KEY_LEFT]) {
            if (player->position.x >= 0.0f) {
                player->position.x -= velocity;
                if (ball->stuck)
                    ball->position.x -= velocity;
            }
        }
        if (this->keys[GLFW_KEY_RIGHT]) {
            if (player->position.x <= this->width - player->size.x) {
                player->position.x += velocity;
                if (ball->stuck)
                    ball->position.x += velocity;
            }
        }

        if (this->keys[GLFW_KEY_SPACE])
            ball->stuck = false;
    }
}

void Game::render() {
    if (this->state == GAME_ACTIVE) {
        renderer->drawSprite(ResourceManager::getTexture("background"), glm::vec2(0.0f, 0.0f), glm::vec2(this->width, this->height));
        this->levels[this->level].draw(*renderer);
        player->draw(*renderer);
        ball->draw(*renderer);
    }
}