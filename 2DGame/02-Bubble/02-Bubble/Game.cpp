#include <GL/glew.h>
#include <GL/glut.h>
#include "Game.h"


void Game::init()
{
	bPlay = true;
	glClearColor(0.3f, 0.3f, 0.3f, 1.0f);
	//scene = new MapScene();
	scene = new MenuScene();
	scene->init();
}

bool Game::update(int deltaTime)
{
	scene->update(deltaTime);
	
	return bPlay;
}

void Game::render()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	scene->render();
}

void Game::keyPressed(int key)
{
	keys[key] = true;
}

void Game::exit() {
	bPlay = false;
}

void Game::keyReleased(int key)
{
	keys[key] = false;
}

void Game::specialKeyPressed(int key)
{
	specialKeys[key] = true;
}

void Game::specialKeyReleased(int key)
{
	specialKeys[key] = false;
}

void Game::mouseMove(int x, int y)
{
}

void Game::mousePress(int button)
{
}

void Game::mouseRelease(int button)
{
}

bool Game::getKey(int key) const
{
	return keys[key];
}

bool Game::getSpecialKey(int key) const
{
	return specialKeys[key];
}

bool Game::movementKeyPressed() {
	return 
		Game::instance().getSpecialKey(GLUT_KEY_RIGHT) ||
		Game::instance().getSpecialKey(GLUT_KEY_LEFT) ||
		Game::instance().getSpecialKey(GLUT_KEY_UP) ||
		Game::instance().getSpecialKey(GLUT_KEY_DOWN);
}

void Game::changeScene(int id) {

	delete scene;
	if ((id - 1) < 5) {
		scene = new MapScene();
		scene->init(id);
	}
	else if ((id - 1) == 5) {
		scene = new InstructionsScene();
		scene->init();
	}
	else if ((id - 1) == 6) {
		scene = new creditsScene();
		scene->init(); 
	}
	else {
		scene = new MenuScene();
		scene->init();
	}
}

void Game::runConsole() {
	FILE* fp;
	AllocConsole();
	freopen_s(&fp, "CONIN$", "r", stdin);
	freopen_s(&fp, "CONOUT$", "w", stdout);
	freopen_s(&fp, "CONOUT$", "w", stderr);
}





