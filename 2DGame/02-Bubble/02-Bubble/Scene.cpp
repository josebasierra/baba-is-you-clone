#include <iostream>
#include <cmath>
#include <glm/gtc/matrix_transform.hpp>
#include "Scene.h"
#include "Game.h"
#include <GL/glew.h>
#include <GL/glut.h>

#define SCREEN_X 32
#define SCREEN_Y 16

#define INIT_PLAYER_X_TILES 4
#define INIT_PLAYER_Y_TILES 25


#define TURN_TIME 200

Scene::Scene()
{
	map = NULL;
}

Scene::~Scene()
{
	if(map != NULL)
		delete map;
}


void Scene::init()
{
	initShaders();
	//map = TileMap::createTileMap("levels/level01.txt", glm::vec2(SCREEN_X, SCREEN_Y), texProgram);
	map = new Map(glm::ivec2(SCREEN_X, SCREEN_Y), glm::ivec2(12, 12), glm::ivec2(32, 32));
	
	Object* object = new Object(map, texProgram, ITEM, BABA);
	object->moveTo(3, 3);
	object->addProperty(IS_YOU);
	objects.push_back(*object);


	/*for (int i = 0; i < 2; i++) {
		object = new Object(glm::ivec2(SCREEN_X, SCREEN_Y), texProgram, ITEM, ROCK);
		object->setPosition(glm::vec2(INIT_PLAYER_X_TILES * map->getTileSize() + (i*1.f), INIT_PLAYER_Y_TILES * map->getTileSize()));
		object->setTileMap(map);

		objects.push_back(*object);
	}*/

	projection = glm::ortho(0.f, float(SCREEN_WIDTH - 1), float(SCREEN_HEIGHT - 1), 0.f);
	currentTime = 0.0f;
}

void Scene::update(int deltaTime)
{
	currentTime += deltaTime;

	//update object animations
	for (int i = 0; i < objects.size(); i++)
		objects[i].update(deltaTime);

	//update turn
	currentTurnTime += deltaTime;
	if (Game::instance().movementKeyPressed() && currentTurnTime >= float(TURN_TIME) ) {
		
		for (int i = 0; i < objects.size(); i++)
			objects[i].updateTurn();

		currentTurnTime = 0;
	}

	//map-> check new rules (remove all properties and apply new ones, transform objects)



}

void Scene::render()
{
	glm::mat4 modelview;

	texProgram.use();
	texProgram.setUniformMatrix4f("projection", projection);
	texProgram.setUniform4f("color", 1.0f, 1.0f, 1.0f, 1.0f);
	modelview = glm::mat4(1.0f);
	texProgram.setUniformMatrix4f("modelview", modelview);
	texProgram.setUniform2f("texCoordDispl", 0.f, 0.f);

	map->render();
}

void Scene::initShaders()
{
	Shader vShader, fShader;

	vShader.initFromFile(VERTEX_SHADER, "shaders/texture.vert");
	if(!vShader.isCompiled())
	{
		cout << "Vertex Shader Error" << endl;
		cout << "" << vShader.log() << endl << endl;
	}
	fShader.initFromFile(FRAGMENT_SHADER, "shaders/texture.frag");
	if(!fShader.isCompiled())
	{
		cout << "Fragment Shader Error" << endl;
		cout << "" << fShader.log() << endl << endl;
	}
	texProgram.init();
	texProgram.addShader(vShader);
	texProgram.addShader(fShader);
	texProgram.link();
	if(!texProgram.isLinked())
	{
		cout << "Shader Linking Error" << endl;
		cout << "" << texProgram.log() << endl << endl;
	}
	texProgram.bindFragmentOutput("outColor");
	vShader.free();
	fShader.free();
}



