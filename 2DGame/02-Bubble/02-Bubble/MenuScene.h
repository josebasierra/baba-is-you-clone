#pragma once
#include "BaseScene.h"
#include "Game.h"
#include <GL/glew.h>
#include <GL/glut.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

class MenuScene : public BaseScene
{
public:
	MenuScene();
	~MenuScene();

	void init();
	void update(int deltaTime);
	void render();
	void loadSprites();

private:
	struct Option {
		Sprite* sprite;
		Texture spritesheet;
	};
	
	Option* options = new Option[7]; 
	int option; //opcion seleccionada
	float currentTime;
	float currentTurnTime;
};

