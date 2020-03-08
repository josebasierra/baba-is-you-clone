#include "Map.h"
#include <iostream>



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


void Map::move(Object* object, ivec2 pos1, ivec2 pos2) {
	remove(object, pos1);
	add(object, pos2);
}

bool Map::isValidPosition(ivec2 pos) {
	return pos.x < mapSize.x && pos.y < mapSize.y && pos.x >= 0 && pos.y >= 0;
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