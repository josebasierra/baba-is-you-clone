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


class MapScene:public BaseScene
{

public:
	MapScene();
	~MapScene();

	void init();
	void update(int deltaTime);
	void render();


private:
	bool initMap(const string& levelFile);
	void runConsole();

private:
	Map *map;
	vector<Object*> objects;
	float currentTime;
	float currentTurnTime;
};


#endif // _SCENE_INCLUDE

