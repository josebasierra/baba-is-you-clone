#ifndef _SCENE_INCLUDE
#define _SCENE_INCLUDE

#include "BaseScene.h"

#include <glm/glm.hpp>
#include "ShaderProgram.h"
#include "Map.h"
#include "Player.h"
#include <vector>
#include "Object.h"
#include <irrKlang.h>
#include <ik_ISoundEngine.h>
using namespace irrklang;


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

private:
	Map *map;
	vector<Object*> objects;
	float currentTime;
	float currentTurnTime;

	int level; //level actual, para saber cual es el siguiente

	vec2 camera;

	irrklang::ISoundEngine* engine; //para la musica del juego

};


#endif // _SCENE_INCLUDE

