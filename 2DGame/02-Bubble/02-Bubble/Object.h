#pragma once

#include "Sprite.h"
#include <unordered_set>

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
	Object(Sprite *sprite, ShaderProgram &shaderProgram,  ObjectType type, ObjectName name);
	~Object();

	void init(const glm::ivec2 &tileMapPos, ShaderProgram &shaderProgram);
	void update(int deltaTime);
	void render();

private:
	Sprite *sprite;
	ObjectType type;
	ObjectName name;

	unordered_set<Property> properties;

};

