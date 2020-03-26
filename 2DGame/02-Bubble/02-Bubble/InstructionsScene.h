#pragma once
#include "BaseScene.h"

class InstructionsScene : public BaseScene
{
public:
	InstructionsScene();
	~InstructionsScene();

	void init();
	void update(int deltaTime);
	void render();
	void changeBackgroud();

private:
	struct Window {
		Sprite* sprite;
		Texture spritesheet;
	};

	Window* windows = new Window[3];
	int window; //para la pagina en la que me encuentro
	float currentTime;
	float currentTurnTime;
};

