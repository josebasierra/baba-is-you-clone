#pragma once
#include <glm/glm.hpp>
#include <vector>
#include <queue>
#include "Object.h"
#include <iostream>

using namespace glm;


class Object;

class Map
{

public:
	Map( ivec2 mapOrigin, ivec2 mapSize, ivec2 tileSize);

	ivec2 getOrigin();
	ivec2 getTileSize();

	void add(Object* object, ivec2 position);
	void remove(Object* object, ivec2 position);
	bool move(Object* object, ivec2 pos_start, ivec2 pos_end);

	bool isValidPosition(ivec2 pos);

	// return true if there's STOP(and not PUSH) item
	bool isBlocked(ivec2 pos, ivec2 dir);

	bool canMove(ivec2 pos, ivec2 dir);

	void render();

private:

	vector<queue<Object*> > grid;
	glm::ivec2 mapOrigin;
	glm::ivec2 mapSize;
	glm::ivec2 tileSize;

};
