#pragma once
#include <glm/glm.hpp>
#include <vector>
#include <queue>
#include <iostream>
#include "Object.h"
#include "ObjectEnums.h"

using namespace glm;


class Object;
class Map
{

public:

	Map(ivec2 mapOrigin, ivec2 mapSize, ivec2 tileSize);

	ivec2 getOrigin();
	ivec2 getTileSize();

	void add(Object* object, ivec2 position);
	void remove(Object* object, ivec2 position);
	bool move(Object* object, ivec2 pos_start, ivec2 pos_end);

	bool isValidPosition(ivec2 pos);

	// return true if there's STOP(and not PUSH) item
	bool isBlocked(ivec2 pos);

	bool canMove(ivec2 pos, ivec2 dir);

	bool pushObjects(ivec2 pos, ivec2 dir);

	Object* getWord(int x, int y);
	void applyAllRules();
	void applyRule(Object* w1, Object* w2, Object* w3);
	void addProperty(ObjectName itemName, ObjectName propertyName);

	void render();



private:

	vector<queue<Object*> > grid;
	glm::ivec2 mapOrigin;
	glm::ivec2 mapSize;
	glm::ivec2 tileSize;

};
