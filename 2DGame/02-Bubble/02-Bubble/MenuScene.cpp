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
	
	//musica para menu...
}

void MenuScene::loadSprites() {
	
	options[0].spritesheet.loadFromFile("images/Instructions.png", TEXTURE_PIXEL_FORMAT_RGBA);
	options[0].sprite = Sprite::createSprite(glm::ivec2(180, 40), glm::vec2(1.f , 1.f), &options[0].spritesheet, &texProgram);
	options[0].sprite->setPosition(vec2(float(SCREEN_WIDTH - 350), float(SCREEN_HEIGHT - 50)));

	options[1].spritesheet.loadFromFile("images/Credits.png", TEXTURE_PIXEL_FORMAT_RGBA);
	options[1].sprite = Sprite::createSprite(glm::ivec2(100, 40), glm::vec2(1.f, 1.f), &options[1].spritesheet, &texProgram);
	options[1].sprite->setPosition(vec2(float(SCREEN_WIDTH - 150), float(SCREEN_HEIGHT - 50)));

	//pasarlo a bucle...
	options[2].spritesheet.loadFromFile("images/level_image1.png", TEXTURE_PIXEL_FORMAT_RGBA);
	options[2].sprite = Sprite::createSprite(glm::ivec2(194, 151), glm::vec2(1.f, 1.f), &options[2].spritesheet, &texProgram);
	options[2].sprite->setPosition(vec2(51.6, 337));
		
	options[3].spritesheet.loadFromFile("images/level_image2.png", TEXTURE_PIXEL_FORMAT_RGBA);
	options[3].sprite = Sprite::createSprite(glm::ivec2(194, 151), glm::vec2(1.f, 1.f), &options[3].spritesheet, &texProgram);
	options[3].sprite->setPosition(vec2(297.2, 337));
	
	options[4].spritesheet.loadFromFile("images/level_image3.png", TEXTURE_PIXEL_FORMAT_RGBA);
	options[4].sprite = Sprite::createSprite(glm::ivec2(194, 151), glm::vec2(1.f, 1.f), &options[4].spritesheet, &texProgram);
	options[4].sprite->setPosition(vec2(542.8, 337));
	
	options[5].spritesheet.loadFromFile("images/level_image4.png", TEXTURE_PIXEL_FORMAT_RGBA);
	options[5].sprite = Sprite::createSprite(glm::ivec2(194, 151), glm::vec2(1.f, 1.f), &options[5].spritesheet, &texProgram);
	options[5].sprite->setPosition(vec2(785.4, 337));
	
	options[6].spritesheet.loadFromFile("images/level_image5.png", TEXTURE_PIXEL_FORMAT_RGBA);
	options[6].sprite = Sprite::createSprite(glm::ivec2(194, 151), glm::vec2(1.f, 1.f), &options[6].spritesheet, &texProgram);
	options[6].sprite->setPosition(vec2(1028, 337));
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

	for (int i = 0; i < 7; i++) {
		options[i].sprite->render();
	}
}