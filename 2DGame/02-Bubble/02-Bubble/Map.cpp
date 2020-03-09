#include "Map.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

#define TURN_TIME 1000  //min millisecs between actions

Map::Map(ivec2 mapOrigin, ivec2 mapSize, ivec2 tileSize) {
	this->mapOrigin = mapOrigin;
	this->mapSize = mapSize;
	this->tileSize = tileSize;
	
	grid = vector<queue<Object*>>(mapSize.x * mapSize.y);
}


ivec2 Map::getOrigin() {
	return mapOrigin;
}

ivec2 Map::getTileSize() {
	return tileSize;
}


void Map::add(Object* object, ivec2 position) {
	grid[position.x * mapSize.x + position.y].push(object);
}


void Map::remove(Object* object, ivec2 position) {
	queue<Object*> q = grid[position.x * mapSize.x + position.y];
	for (int i = 0; i < q.size(); i++) {
		Object* object = q.front();
		q.pop();
		if (object != object) q.push(object);
	}
}


bool Map::move(Object* object, ivec2 pos1, ivec2 pos2) {
	ivec2 dir = pos2 - pos1;
	if (canMove(pos1, dir)) {
		remove(object, pos1);
		add(object, pos2);
		return true;
	}

	return false;

}


bool Map::isValidPosition(ivec2 pos) {
	return pos.x < mapSize.x && pos.y < mapSize.y && pos.x >= 0 && pos.y >= 0;
}

//temporal, cambiar
bool Map::isBlocked(ivec2 pos, ivec2 dir) {
	ivec2 pos2 = pos + dir; 
	queue<Object*> q = grid[pos2.x * mapSize.x + pos2.y];

	bool isBlocked = false;
	for (int i = 0; i < q.size(); i++) {
		Object* object = q.front();
		q.pop();
		if (object->hasProperty(IS_STOP) && !object->hasProperty(IS_PUSH) && !object->hasProperty(IS_YOU)) isBlocked = true;
		q.push(object);
	}

	return isBlocked;
}

// can move in direction "dir" from position "pos" ??
bool Map::canMove(ivec2 pos, ivec2 dir) {
	return (isValidPosition(pos + dir) && !isBlocked(pos, dir));
}

void Map::render() {
	for (int x = 0; x < mapSize.x; x++) {
		for (int y = 0; y < mapSize.y; y++) {
			queue<Object*> q = grid[x * mapSize.x + y];
			for (int z = 0; z < q.size(); z++) {
				Object* object = q.front();
				object->render();
				q.pop();
				q.push(object);
			}
		}
	}
}

