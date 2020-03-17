#pragma once

#include "Sprite.h"
#include <unordered_set>
#include "Map.h"
#include "ObjectEnums.h"

using namespace glm;


class Map;
class Object
{
public:

	Object(Map* map,  ShaderProgram& shaderProgram, ObjectType type, ObjectName name);
	~Object();

	void loadSprite();
	void transform(ObjectType type, ObjectName name);

	ObjectType getType();
	ObjectName getName();

	void update(int deltaTime);
	void render();

	//object can move again
	void refresh();

	void updateTurn();

	bool moveTo(ivec2 pos);
	bool moveTo(int x, int y);
	bool setPos(int x, int y);

	bool isWord();

	void addProperty(ObjectName name);
	void addProperty(Property property);

	void removeProperty(Property property);
	void cleanProperties();
	bool hasProperty(Property property);


private:

	Sprite *sprite;
	Texture spritesheet;
	ShaderProgram* shaderProgram;

	ObjectType type;
	ObjectName name;

	ivec2 pos;
	bool hasMoved;

	unordered_set<Property> properties;

	Map* map; 
};

