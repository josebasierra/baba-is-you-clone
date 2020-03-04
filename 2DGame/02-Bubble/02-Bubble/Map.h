#pragma once
#include <glm/glm.hpp>
#include <vector>
#include "Object.h"
#include <iostream>

class Object;

class Map
{

public:
	Map(glm::ivec2 mapOrigin, glm::ivec2 mapSize, glm::ivec2 tileSize);

	glm::ivec2 getOrigin();
	
	glm::ivec2 getTileSize();


private:

	vector<Object*> layer0;
	vector<Object*> layer1;

	glm::ivec2 mapOrigin;
	glm::ivec2 mapSize;
	glm::ivec2 tileSize;

};
