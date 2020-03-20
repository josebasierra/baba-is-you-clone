#include <iostream>
#include <cmath>
#include <glm/gtc/matrix_transform.hpp>
#include "MapScene.h"
#include "Game.h"
#include <GL/glew.h>
#include <GL/glut.h>
#include <fstream>
#include <sstream>
#include <vector>
<<<<<<< HEAD:2DGame/02-Bubble/02-Bubble/MapScene.cpp
=======
#include <windows.h>
#include <mmsystem.h>
#include <irrKlang.h>
using namespace irrklang;
>>>>>>> 9b34fd9a11a0c92575e509c7177a8004771d6a81:2DGame/02-Bubble/02-Bubble/Scene.cpp

#pragma comment(lib, "irrKlang.lib") 

#define SCREEN_X 32
#define SCREEN_Y 16

#define INIT_PLAYER_X_TILES 4
#define INIT_PLAYER_Y_TILES 25

#define TURN_TIME 200


MapScene::MapScene()
{
	map = NULL;
	currentTime = 0.0f;
	currentTurnTime = 0.0f;
}

MapScene::~MapScene()
{
	if(map != NULL)
		delete map;
}


void MapScene::init()
{
	BaseScene::init();

	//runConsole();

<<<<<<< HEAD:2DGame/02-Bubble/02-Bubble/MapScene.cpp
	//load and init map 
	initMap("levels/level1.txt");

	//load background
=======
	initShaders();
	init_Scene("levels/level1.txt");

	
>>>>>>> 9b34fd9a11a0c92575e509c7177a8004771d6a81:2DGame/02-Bubble/02-Bubble/Scene.cpp
	spritesheet.loadFromFile("images/black.png", TEXTURE_PIXEL_FORMAT_RGBA);
	background = Sprite::createSprite(map->getMapTotalSize(), glm::vec2(1.f, 1.f), &spritesheet, &texProgram);
	background->setPosition(map->getOrigin());

	//init camera
	projection = glm::ortho(0.f, float(SCREEN_WIDTH - 1), float(SCREEN_HEIGHT - 1), 0.f);

<<<<<<< HEAD:2DGame/02-Bubble/02-Bubble/MapScene.cpp
}


void MapScene::update(int deltaTime)
{
	currentTime += deltaTime;

	//update object animations
	for (int i = 0; i < objects.size(); i++)
		objects[i]->update(deltaTime);

	//update turn
	currentTurnTime += deltaTime;
	if (Game::instance().movementKeyPressed() && currentTurnTime >= float(TURN_TIME) ) {

		//refresh objects (hasMoved = false)
		for (int i = 0; i < objects.size(); i++)
			objects[i]->refresh();

		//apply movement to objects
		for (int i = 0; i < objects.size(); i++)
			objects[i]->updateTurn();

		//remove all properties (except words)
		for (int i = 0; i < objects.size(); i++) {
			Object* obj = objects[i];
			if (!obj->isWord()) obj->cleanProperties();
		}

		//check rules and apply new properties
		map->applyAllRules();

		currentTurnTime = 0;
	}

=======
	map->applyAllRules();
	
	ISoundEngine* engine = createIrrKlangDevice();
	if (!engine)
		cout << "error";
	engine->play2D("music/baba_is_you_ost.wav", true);
	
>>>>>>> 9b34fd9a11a0c92575e509c7177a8004771d6a81:2DGame/02-Bubble/02-Bubble/Scene.cpp
}


void MapScene::render()
{
	glm::mat4 modelview;

	texProgram.use();
	texProgram.setUniformMatrix4f("projection", projection);
	texProgram.setUniform4f("color", 1.0f, 1.0f, 1.0f, 1.0f);
	modelview = glm::mat4(1.0f);
	texProgram.setUniformMatrix4f("modelview", modelview);
	texProgram.setUniform2f("texCoordDispl", 0.f, 0.f);

	background->render();
	map->render();
}


bool MapScene::initMap(const string& levelFile) {
	//obtengo datos del file

	ifstream fin;
	string line, tilesheetFile;
	stringstream sstream;
	int tile;
	ivec2 mapSize;
	ivec2 tileSize;

	fin.open(levelFile.c_str());
	if (!fin.is_open())
		return false;
	getline(fin, line);
	if (line.compare(0, 7, "TILEMAP") != 0)
		return false;
	getline(fin, line);
	sstream.str(line);
	sstream >> mapSize.x >> mapSize.y;
	getline(fin, line);
	sstream.str(line);
	sstream >> tileSize.x >> tileSize.y;
	map = new Map(glm::ivec2(SCREEN_X, SCREEN_Y), mapSize, tileSize);

	for (int y = 0; y < mapSize.y; y++)
	{
		for (int x = 0; x < mapSize.x; x++)
		{
			fin >> tile;
			if (tile == 1) {
				Object* object = new Object(map, texProgram, ITEM, BABA);
				object->setPos(x, y);
				objects.push_back(object);
			}
			else if (tile == 2) {
				Object* object = new Object(map, texProgram, ITEM, ROCK);
				object->setPos(x, y);
				objects.push_back(object);
			}
			else if (tile == 3) {
				Object* object = new Object(map, texProgram, ITEM, WALL);
				object->setPos(x, y);
				objects.push_back(object);
			}
			else if (tile == 4) {
				Object* object = new Object(map, texProgram, ITEM, FLAG);
				object->setPos(x, y);
				objects.push_back(object);
			}
			else if (tile == 5) {
				Object* object = new Object(map, texProgram, NOUN, BABA);
				object->setPos(x, y);
				object->addProperty(IS_PUSH);
				objects.push_back(object);
			}
			else if (tile == 6) {
				Object* object = new Object(map, texProgram, OPERATOR, IS);
				object->setPos(x, y);
				object->addProperty(IS_PUSH);
				objects.push_back(object);
			}
			else if (tile == 7) {
				Object* object = new Object(map, texProgram, PROPERTY, YOU);
				object->setPos(x, y);
				object->addProperty(IS_PUSH);
				objects.push_back(object);
			}
			else if (tile == 8) {
				Object* object = new Object(map, texProgram, NOUN, FLAG);
				object->setPos(x, y);
				object->addProperty(IS_PUSH);
				objects.push_back(object);
			}
			else if (tile == 9) {
				Object* object = new Object(map, texProgram, PROPERTY, WIN);
				object->setPos(x, y);
				object->addProperty(IS_PUSH);
				objects.push_back(object);
			}
			else if (tile == 10) {
				Object* object = new Object(map, texProgram, NOUN, WALL);
				object->setPos(x, y);
				object->addProperty(IS_PUSH);
				objects.push_back(object);
			}
			else if (tile == 11) {
				Object* object = new Object(map, texProgram, PROPERTY, STOP);
				object->setPos(x, y);
				object->addProperty(IS_PUSH);
				objects.push_back(object);
			}
			else if (tile == 12) {
				Object* object = new Object(map, texProgram, NOUN, ROCK);
				object->setPos(x, y);
				object->addProperty(IS_PUSH);
				objects.push_back(object);
			}
			else if (tile == 13) {
				Object* object = new Object(map, texProgram, PROPERTY, PUSH);
				object->setPos(x, y);
				object->addProperty(IS_PUSH);
				objects.push_back(object);
			}
			else if (tile == 14) {
				Object* object = new Object(map, texProgram, ITEM, SKULL);
				object->setPos(x, y);
				objects.push_back(object);
			}
			else if (tile == 15) {
				Object* object = new Object(map, texProgram, NOUN, SKULL);
				object->setPos(x, y);
				object->addProperty(IS_PUSH);
				objects.push_back(object);
			}
			else if (tile == 16) {
				Object* object = new Object(map, texProgram, PROPERTY, DEFEAT);
				object->setPos(x, y);
				object->addProperty(IS_PUSH);
				objects.push_back(object);
			}
			else if (tile == 17) {
				Object* object = new Object(map, texProgram, OPERATOR, AND);
				object->setPos(x, y);
				object->addProperty(IS_PUSH);
				objects.push_back(object);
			}
		}
#ifndef _WIN32
		fin.get(tile);
#endif
	}
	fin.close();

	map->applyAllRules();
	return true;
}

void MapScene::runConsole() {
	FILE* fp;

<<<<<<< HEAD:2DGame/02-Bubble/02-Bubble/MapScene.cpp
	AllocConsole();
	freopen_s(&fp, "CONIN$", "r", stdin);
	freopen_s(&fp, "CONOUT$", "w", stdout);
	freopen_s(&fp, "CONOUT$", "w", stderr);
=======
void Scene::update(int deltaTime)
{
	currentTime += deltaTime;

	//update object animations
	for (int i = 0; i < objects.size(); i++)
		objects[i]->update(deltaTime);

	//update turn
	currentTurnTime += deltaTime;
	if (Game::instance().movementKeyPressed() && currentTurnTime >= float(TURN_TIME) ) {

		//refresh objects (hasMoved = false)
		for (int i = 0; i < objects.size(); i++)
			objects[i]->refresh();

		//apply movement to objects
		for (int i = 0; i < objects.size(); i++)
			objects[i]->updateTurn();

		//remove all properties (except words)
		for (int i = 0; i < objects.size(); i++) {
			Object* obj = objects[i];
			if (!obj->isWord()) obj->cleanProperties();
		}

		//check rules and apply new properties
		map->applyAllRules();

		currentTurnTime = 0;
	}

	

	//apply new rules properties
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

	background->render();
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
>>>>>>> 9b34fd9a11a0c92575e509c7177a8004771d6a81:2DGame/02-Bubble/02-Bubble/Scene.cpp
}
