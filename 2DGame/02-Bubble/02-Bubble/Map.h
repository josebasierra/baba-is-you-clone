#pragma once
#include <glm/glm.hpp>
#include <vector>
#include "Object.h"
#include <iostream>


class Map
{

public:
	Map(glm::ivec2 mapOrigin, glm::ivec2 mapSize, glm::ivec2 tileSize);
	~Map();

	glm::ivec2 get_origin();
	
	glm::ivec2 get_tileSize();


private:

	vector<Object> layer0;
	vector<Object> layer1;

	glm::ivec2 mapOrigin;
	glm::ivec2 mapSize;
	glm::ivec2 tileSize;

};
