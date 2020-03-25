#include "MenuScene.h"


MenuScene::MenuScene() {}

MenuScene:: ~MenuScene() {}

void MenuScene::init() {
	BaseScene::init();

	spritesheet.loadFromFile("images/menu.png", TEXTURE_PIXEL_FORMAT_RGBA);
	background = Sprite::createSprite(vec2(1280.0,720.0), glm::vec2(1.f, 1.f), &spritesheet, &texProgram);
	background->setPosition(vec2(0.0,0.0));

	projection = glm::ortho(0.f, float(SCREEN_WIDTH - 1), float(SCREEN_HEIGHT - 1), 0.f);
	
	loadSprites();
	
	option = 0; //mapa 1 seleccionado al inicio
	
	//musica para menu...
}

void MenuScene::loadSprites() {
	
	for (int i = 0; i <= 4; ++i) {
		options[i].spritesheet.loadFromFile("images/level_image" + to_string(i+1) + ".png", TEXTURE_PIXEL_FORMAT_RGBA);
		options[i].sprite = Sprite::createSprite(glm::ivec2(194, 151), glm::vec2(1.f, 1.f), &options[i].spritesheet, &texProgram);
		options[i].sprite->setPosition(vec2(51.6+(i*245.6), 337));
	}
	
	options[5].spritesheet.loadFromFile("images/Instructions.png", TEXTURE_PIXEL_FORMAT_RGBA);
	options[5].sprite = Sprite::createSprite(glm::ivec2(270, 60), glm::vec2(1.f , 1.f), &options[5].spritesheet, &texProgram);
	options[5].sprite->setPosition(vec2(float(SCREEN_WIDTH - 500), float(SCREEN_HEIGHT - 60)));

	options[6].spritesheet.loadFromFile("images/Credits.png", TEXTURE_PIXEL_FORMAT_RGBA);
	options[6].sprite = Sprite::createSprite(glm::ivec2(150, 60), glm::vec2(1.f, 1.f), &options[6].spritesheet, &texProgram);
	options[6].sprite->setPosition(vec2(float(SCREEN_WIDTH - 200), float(SCREEN_HEIGHT - 60)));
}

void MenuScene::update(int deltaTime) {
	currentTime += deltaTime;
	
	if (Game::instance().getSpecialKey(GLUT_KEY_RIGHT)) {
		if (option < 6) ++option;
		else option == 0;
	}

	if (Game::instance().getSpecialKey(GLUT_KEY_LEFT)) {
		if (option > 0) --option;
		else option == 6;
	}

	if (Game::instance().getKey(GLUT_KEY_ENTER)) {
		Game::instance().changeScene(option+1);
	}
}

void MenuScene::render() {
	glm::mat4 modelview;

	texProgram.use();
	texProgram.setUniformMatrix4f("projection", projection);
	texProgram.setUniform4f("color", 1.0f, 1.0f, 1.0f, 1.0f);
	modelview = glm::mat4(1.0f);
	texProgram.setUniformMatrix4f("modelview", modelview);
	texProgram.setUniform2f("texCoordDispl", 0.f, 0.f);

	background->render();
	
	for (int i = 0; i < 7; i++) {
		if (option != i) options[i].sprite->render();
		else options[i].sprite->select();
	}
		
	
}