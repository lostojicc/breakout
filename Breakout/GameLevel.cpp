#include "GameLevel.h"

void GameLevel::load(const char* file, unsigned int levelWidth, unsigned int levelHeight) {
	this->bricks.clear();

	unsigned int tileCode;
	std::string line;
	std::ifstream fstream(file);
	std::vector<std::vector<unsigned int>> tileData;
	if (fstream) {
		while (std::getline(fstream, line)) {
			std::istringstream sstream(line);
			std::vector<unsigned int> row;
			while (sstream >> tileCode)
				row.push_back(tileCode);
			tileData.push_back(row);
		}

		if (tileData.size())
			this->init(tileData, levelWidth, levelHeight);
	}
}

void GameLevel::init(std::vector<std::vector<unsigned int>> tileData, unsigned int levelWidth, unsigned int levelHeight) {
	unsigned int height = tileData.size();
	unsigned int width = tileData[0].size();
	float unitWidth = levelWidth / static_cast<float>(width), unitHeight = levelHeight / static_cast<float>(height);

	for (unsigned int y = 0; y < height; y++) {
		for (unsigned int x = 0; x < width; x++) {
			unsigned int tile = tileData[y][x];
			
			if (!tile)
				continue;

			glm::vec2 pos(unitWidth * x, unitHeight * y);
			glm::vec2 size(unitWidth, unitHeight);
			glm::vec3 color = glm::vec3(0.0f);

			switch (tile) {
				case 1:
					this->bricks.push_back(GameObject(pos, size, ResourceManager::getTexture("block_solid"), true));
					break;
				case 2:
					color = glm::vec3(1.0f, 0.75f, 0.8f);
					this->bricks.push_back(GameObject(pos, size, ResourceManager::getTexture("block"), false, glm::vec2(0.0f, 0.0f), color));
					break;
				case 3:
					color = glm::vec3(1.0f, 0.08f, 0.58f);
					this->bricks.push_back(GameObject(pos, size, ResourceManager::getTexture("block"), false, glm::vec2(0.0f, 0.0f), color));
					break;
				case 4:
					color = glm::vec3(0.85f, 0.44f, 0.84f);
					this->bricks.push_back(GameObject(pos, size, ResourceManager::getTexture("block"), false, glm::vec2(0.0f, 0.0f), color));
					break;
				default:
					color = glm::vec3(0.58f, 0.0f, 0.83f);
					this->bricks.push_back(GameObject(pos, size, ResourceManager::getTexture("block"), false, glm::vec2(0.0f, 0.0f), color));
					break;
			}
		}
	}
}

void GameLevel::draw(SpriteRenderer& renderer) {
	for (GameObject& tile : this->bricks) {
		if (!tile.isDestroyed)
			tile.draw(renderer);
	}
}

bool GameLevel::isCompleted() {
	for (const GameObject& tile : this->bricks) {
		if (!tile.isSolid && !tile.isDestroyed)
			return false;
	}
	return true;
}