#include "Map.h"


Map::Map(glm::ivec2 mapOrigin, glm::ivec2 mapSize, glm::ivec2 tileSize) {
	this->mapOrigin = mapOrigin;
	this->mapSize = mapSize;
	this->tileSize = tileSize;

	layer0 = vector<Object>(mapSize.x * mapSize.y);
	layer1 = vector<Object>(mapSize.x * mapSize.y);
}

glm::ivec2 Map::get_origin() {
	return mapOrigin;
}

glm::ivec2 Map::get_tileSize() {
	return tileSize;
}
