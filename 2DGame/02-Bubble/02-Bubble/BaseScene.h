#pragma once
#include <glm/glm.hpp>
#include "ShaderProgram.h"
#include "Sprite.h"
#include <irrKlang.h>
#include <ik_ISoundEngine.h>
using namespace irrklang;


#define TURN_TIME 200

// Scene contains all the entities of our game.
// It is responsible for updating and render them.


class BaseScene
{

public:
	void virtual init();
	void virtual init(int level);
	void virtual update(int deltaTime);
	void virtual render();


protected:
	void initShaders();

protected:
	Sprite* background;
	Texture spritesheet;
	ShaderProgram texProgram;
	glm::mat4 projection;

	float currentTime;
	float currentTurnTime;

	irrklang::ISoundEngine* engine; //para la musica del juego

};
