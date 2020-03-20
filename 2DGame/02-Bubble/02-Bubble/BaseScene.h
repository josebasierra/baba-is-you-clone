#pragma once
#include <glm/glm.hpp>
#include "ShaderProgram.h"
#include "Sprite.h"
#include "SceneEnums.h"



// Scene contains all the entities of our game.
// It is responsible for updating and render them.


class BaseScene
{

public:
	void virtual init();
	void virtual update(int deltaTime);
	void virtual render();


protected:
	void initShaders();

protected:
	Sprite* background;
	Texture spritesheet;

	ShaderProgram texProgram;

	glm::mat4 projection;

};
