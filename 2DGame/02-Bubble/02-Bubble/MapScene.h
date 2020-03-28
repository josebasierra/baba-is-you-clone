#ifndef _SCENE_INCLUDE
#define _SCENE_INCLUDE

#include "BaseScene.h"

#include <glm/glm.hpp>
#include "ShaderProgram.h"
#include "Map.h"
#include "Player.h"
#include <vector>
#include "Object.h"



// Scene contains all the entities of our game.
// It is responsible for updating and render them.


class MapScene: public BaseScene
{

public:
	MapScene();
	~MapScene();

	void init(int level);
	void update(int deltaTime);
	void render();

private:
	bool initMap(const string& levelFile);
	void updateMapLogic();

private:
	Map *map;
	vector<Object*> objects;

	bool winState, loseState;
	bool enteredLoseState; 

	int currentLevel; 
	vec2 camera;

	Sprite* instructions;
	Texture spritesheetinst;
};


#endif // _SCENE_INCLUDE

