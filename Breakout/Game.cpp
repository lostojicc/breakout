#include "Game.h"

Game::Game(unsigned int width, unsigned int height)
    : state(GAME_ACTIVE), keys(), width(width), height(height) {
}

Game::~Game() {}

void Game::Init() {}

void Game::Update(float dt) {}

void Game::ProcessInput(float dt) {}

void Game::Render() {}