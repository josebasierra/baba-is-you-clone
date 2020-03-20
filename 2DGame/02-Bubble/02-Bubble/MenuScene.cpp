#include "MenuScene.h"


MenuScene::MenuScene() {

}

MenuScene::~MenuScene() {

}

void MenuScene::init() {
	BaseScene::init();

	spritesheet.loadFromFile("images/menu.png", TEXTURE_PIXEL_FORMAT_RGBA);
	background = Sprite::createSprite(vec2(1280.0,720.0), glm::vec2(1.f, 1.f), &spritesheet, &texProgram);
	background->setPosition(vec2(0.0,0.0));

	projection = glm::ortho(0.f, float(SCREEN_WIDTH - 1), float(SCREEN_HEIGHT - 1), 0.f);

	loadSprites();
	//musica para menu...
}

void MenuScene::loadSprites() {
	Sprite* sprite;
	
	/*spritesheet.loadFromFile("images/Instructions.png", TEXTURE_PIXEL_FORMAT_RGBA);
	sprite = Sprite::createSprite(glm::ivec2(90, 20), glm::vec2(1.f , 1.f), &spritesheet, &texProgram);
	sprite->setPosition(vec2(0.0,0.0));
	options.push_back(sprite);*/


	spritesheet.loadFromFile("images/Credits.png", TEXTURE_PIXEL_FORMAT_RGBA);
	sprite = Sprite::createSprite(glm::ivec2(50, 20), glm::vec2(1.f, 1.f), &spritesheet, &texProgram);
	sprite->setPosition(vec2(0.0, 0.0));
	options.push_back(sprite);
}

void MenuScene::update(int deltaTime) {
	//ya se vera...
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
	
	for (int i = 0; i < options.size(); i++) {
		options[i]->render();
	}
}