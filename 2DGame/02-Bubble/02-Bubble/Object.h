#pragma once

#include "Sprite.h"
#include <unordered_set>
#include "Map.h"


using namespace glm;

enum ObjectType
{
	NOUN, OPERATOR, PROPERTY, ITEM
};

enum ObjectName {
	WALL, ROCK, FLAG, BABA,
	IS,
	PUSH, STOP, YOU, WIN
};

enum Property {
	IS_PUSH, IS_STOP, IS_WIN, IS_YOU
};

enum Direction {
	UP, DOWN, RIGHT, LEFT
};


class Map;

class Object
{
public:

	Object(Map* map,  ShaderProgram& shaderProgram, ObjectType type, ObjectName name);
	~Object();

	uint getId();

	void update(int deltaTime);
	void render();

	void updateTurn();

	bool moveTo(ivec2 pos);
	bool moveTo(int x, int y);

	bool setPos(int x, int y);

	void addProperty(Property property);
	void removeProperty(Property property);
	bool hasProperty(Property property);


private:

	Sprite *sprite;
	Texture spritesheet;

	ObjectType type;
	ObjectName name;

	ivec2 pos;

	unordered_set<Property> properties;

	Map* map; 
};

