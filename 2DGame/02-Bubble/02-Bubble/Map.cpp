#include "Map.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

using namespace glm;


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

ivec2 Map::getMapTotalSize() {
	return tileSize * mapSize;
}


void Map::add(Object* object, ivec2 position) {
	grid[position.y * mapSize.x + position.x].push(object);
}


void Map::remove(Object* object, ivec2 position) {
	queue<Object*> & q = grid[position.y*mapSize.x + position.x] ;
	int n = q.size();
	for (int i = 0; i < n; i++) {
		Object* objectAux = q.front();
		q.pop();
		if (object != objectAux) q.push(objectAux);		
	}
}


bool Map::move(Object* object, ivec2 pos1, ivec2 pos2) {
	ivec2 dir = pos2 - pos1;

	if (isValidPosition(pos2) && !isBlocked(pos2) && pushObjects(pos2, dir)) {
		remove(object, pos1);
		add(object, pos2);
		return true;
	}

	return false;
}


// true if can push objects in grid position 'pos' in direction 'dir'
bool Map::pushObjects(ivec2 pos, ivec2 dir) {
	queue<Object*> & q = grid[pos.y * mapSize.x + pos.x];

	bool canPush = true;
	for (int i = 0; i < q.size(); i++) {
		Object* object = q.front();
		q.pop(); q.push(object);
		if (object->hasProperty(IS_PUSH) && !object->moveTo(pos + dir)) {
			canPush = false;
		}
	} 
	return canPush;
}


bool Map::hasObjectWithProperty(ivec2 pos, Property property) {
	queue<Object*>& q = grid[pos.y * mapSize.x + pos.x];

	bool b = false;
	for (int i = 0; i < q.size(); i++) {
		Object* object = q.front();
		q.pop();
		if (object->hasProperty(property)) b = true;
		q.push(object);
	}
	return b;
}


bool Map::isValidPosition(ivec2 pos) {
	return pos.x < mapSize.x && pos.y < mapSize.y && pos.x >= 0 && pos.y >= 0;
}

//temporal, cambiar
bool Map::isBlocked(ivec2 pos) {
	queue<Object*> & q = grid[pos.y * mapSize.x + pos.x];
	 
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
	return (isValidPosition(pos + dir));
}


Object* Map::getWord(int x, int y) {
	queue<Object*>& q = grid[y * mapSize.x + x];
	Object* word = NULL;
	for (int i = 0; i < q.size(); i++) {
		Object* object = q.front();
		q.pop();
		if (object->isWord()) word = object;
		q.push(object);
	}

	return word;
}


void Map::applyAllRules() {
	for (int x = 0; x < mapSize.x -2; x++) {
		for (int y = 0; y < mapSize.y -2; y++) {

			Object* word = getWord(x,y);

			if (word != NULL && word->getType() == NOUN) {
				applyRule(word, getWord(x+1,y), getWord(x+2, y));
				applyRule(word, getWord(x, y+1), getWord(x, y+2));
			}
		}
	}
}


void Map::applyRule(Object* w1, Object* w2, Object* w3) {
	if (w1 == NULL || w2 == NULL || w3 == NULL) return;
	if (w1->getType() == NOUN && w2->getType() == OPERATOR) {

		// NOUN OPERATOR PROPERTY
		if (w3->getType() == PROPERTY) {
			addProperty(w1->getName(), w3->getName());
		}

		// NOUN OPERATOR NOUN
		else if (w3->getType() == NOUN) {
			transformItems(w1->getName(), w3->getName());
		}
	}
}

void Map::addProperty(ObjectName itemName, ObjectName propertyName) {
	for (int x = 0; x < mapSize.x; x++) {
		for (int y = 0; y < mapSize.y; y++) {
			queue<Object*>& q = grid[y * mapSize.x + x];
			for (int z = 0; z < q.size(); z++) {
				Object* object = q.front();
				
				if (object->getType() == ITEM && object->getName() == itemName)
					object->addProperty(propertyName);

				q.pop();
				q.push(object);
			}
		}
	}
}


void Map::transformItems(ObjectName name1, ObjectName name2) {
	for (int x = 0; x < mapSize.x; x++) {
		for (int y = 0; y < mapSize.y; y++) {
			queue<Object*>& q = grid[y * mapSize.x + x];
			for (int z = 0; z < q.size(); z++) {
				Object* object = q.front();

				if (object->getType() == ITEM && object->getName() == name1) 
					object->transform(ITEM, name2);

				q.pop();
				q.push(object);
			}
		}
	}
}



void Map::render() {
	for (int x = 0; x < mapSize.x; x++) {
		for (int y = 0; y < mapSize.y; y++) {
			queue<Object*>& q = grid[y * mapSize.x + x];
			for (int z = 0; z < q.size(); z++) {
				Object* object = q.front();
				object->render();
				q.pop();
				q.push(object);
			}
		}
	}
}



