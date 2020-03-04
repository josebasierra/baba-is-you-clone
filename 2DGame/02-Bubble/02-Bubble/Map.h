#pragma once
#include <glm/glm.hpp>
#include "Object.h"


class Map
{

public:
	Map(glm::ivec2 mapOrigin, glm::ivec2 mapSize, glm::ivec2 tileSize);
	~Map();

private:

	vector<Object*>* layer0;
	vector<Object*>* layer1;

	glm::ivec2 mapOrigin;
	glm::ivec2 mapSize;
	glm::ivec2 tileSize;

};
