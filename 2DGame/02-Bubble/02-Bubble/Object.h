#pragma once

#include "Sprite.h"
#include <unordered_set>
#include "Map.h"


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


class Map;

class Object
{
public:

	Object(Map* map,  ShaderProgram& shaderProgram, ObjectType type, ObjectName name);
	~Object();

	void update(int deltaTime);
	void render();
	void setPosition(int x, int y);

	void addProperty(Property property);
	void removeProperty(Property property);

private:
	Sprite *sprite;
	Texture spritesheet;

	ObjectType type;
	ObjectName name;

	glm::ivec2 pos;

	unordered_set<Property> properties;

	Map* map; 
	float currentTime;
};

