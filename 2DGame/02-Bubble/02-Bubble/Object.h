#pragma once

#include "Sprite.h"
#include <unordered_set>
#include "TileMap.h"

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

class Object
{
public:
	Object(const glm::ivec2 &tileMapPos, ShaderProgram &shaderProgram,  ObjectType type, ObjectName name);
	~Object();

	void update(int deltaTime);
	void render();
	void setPosition(const glm::vec2 &pos);
	void setTileMap(TileMap *tileMap);

private:
	Sprite *sprite;
	ObjectType type;
	ObjectName name;
	Texture spritesheet;
	glm::ivec2 tileMapDispl, posObject;

	unordered_set<Property> properties;

	TileMap *map;

};

