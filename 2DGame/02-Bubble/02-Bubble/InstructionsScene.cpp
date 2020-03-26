#include "InstructionsScene.h"
#include "Game.h"

#define TURN_TIME 120

InstructionsScene::InstructionsScene() {
	this->window = 0;
	currentTime = 0.0f;
	currentTurnTime = 0.0f;
}

InstructionsScene:: ~InstructionsScene(){}

void InstructionsScene::init() {
	BaseScene::init();

	for (int i = 0; i < 3; ++i) {
		windows[i].spritesheet.loadFromFile("images/instructions" + to_string(window + 1) + ".png", TEXTURE_PIXEL_FORMAT_RGBA);
		windows[i].sprite = Sprite::createSprite(glm::ivec2(1280.0, 720.0), glm::vec2(1.f, 1.f), &windows[i].spritesheet, &texProgram);
		windows[i].sprite->setPosition(vec2(0.0,0.0));
	}
	
	projection = glm::ortho(0.f, float(SCREEN_WIDTH - 1), float(SCREEN_HEIGHT - 1), 0.f);
}

void InstructionsScene::update(int deltaTime) {
	currentTime += deltaTime;
	
	currentTurnTime += deltaTime;
	if (currentTurnTime >= float(TURN_TIME)) {
		if (Game::instance().getSpecialKey(GLUT_KEY_RIGHT)) {
			if (window < 2) ++window;
		}

		if (Game::instance().getSpecialKey(GLUT_KEY_LEFT)) {
			if (window > 0) --window;
		}
		currentTurnTime = 0;
	}

	if (Game::instance().getKey(GLUT_KEY_ESC)) {
		Game::instance().changeScene(8); //cambio a MenuScene
	}
}

void InstructionsScene::render() {
	glm::mat4 modelview;

	texProgram.use();
	texProgram.setUniformMatrix4f("projection", projection);
	texProgram.setUniform4f("color", 1.0f, 1.0f, 1.0f, 1.0f);
	modelview = glm::mat4(1.0f);
	texProgram.setUniformMatrix4f("modelview", modelview);
	texProgram.setUniform2f("texCoordDispl", 0.f, 0.f);

	//render del sprite que nos interesa
	windows[window].sprite->render();
}
