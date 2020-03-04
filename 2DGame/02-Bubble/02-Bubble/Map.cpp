#include "Map.h"


Map::Map(glm::ivec2 mapOrigin, glm::ivec2 mapSize, glm::ivec2 tileSize) {
	this->mapOrigin = mapOrigin;
	this->mapSize = mapSize;
	this->tileSize = tileSize;

	layer0 = new vector<Object*>(mapSize.x * mapSize.y);
	layer1 = new vector<Object*>(mapSize.x * mapSize.y);
}
