#include <iostream>
#include <cmath>
#include <glm/gtc/matrix_transform.hpp>
#include "Scene.h"
#include "Game.h"
#include <GL/glew.h>
#include <GL/glut.h>
#include <fstream>
#include <sstream>
#include <vector>
#include <windows.h>
#include <mmsystem.h>
//#include <SFML/Audio.hpp>


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
	//output console
	/*FILE* fp;

	AllocConsole();
	freopen_s(&fp, "CONIN$", "r", stdin);
	freopen_s(&fp, "CONOUT$", "w", stdout);
	freopen_s(&fp, "CONOUT$", "w", stderr);*/
	//----------------------------------------------

	initShaders();
	//init_Scene("levels/level2.txt");

	
	spritesheet.loadFromFile("images/Menu.png", TEXTURE_PIXEL_FORMAT_RGBA);
	background = Sprite::createSprite(vec2(1280.0,720.0), glm::vec2(1.f, 1.f), &spritesheet, &texProgram);
	background->setPosition(vec2(0.0,0.0));

	projection = glm::ortho(0.f, float(SCREEN_WIDTH - 1), float(SCREEN_HEIGHT - 1), 0.f);
	currentTime = 0.0f;

	//map->applyAllRules();
	

	/*sf::Music music;
	if (!music.openFromFile("music/baba_is_you_ost.wav"))
		cout << "error";
	music.play(); Esto es de la libreria sfml*/
	
	PlaySound(TEXT("music/baba_is_you_ost.wav"),NULL ,SND_ASYNC);
}

bool Scene::init_Scene(const string &levelFile) {
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

	for (int y = 0; y<mapSize.y; y++)
	{
		for (int x = 0; x<mapSize.x; x++)
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

	return true;
}


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
		
		//PlaySound(NULL,NULL, SND_ASYNC);
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
	//map->render();
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



