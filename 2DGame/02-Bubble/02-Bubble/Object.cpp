#include "Object.h"
#include <cmath>
#include <iostream>
#include <GL/glew.h>
#include <GL/glut.h>
#include "Game.h"



Object::Object(Map* map,  ShaderProgram& shaderProgram, ObjectType type, ObjectName name) {
	this->map = map;
	this->name = name;
	this->type = type;

	if (this->name == BABA && this->type == ITEM) {
		spritesheet.loadFromFile("images/baba_anim.png", TEXTURE_PIXEL_FORMAT_RGBA);
		sprite = Sprite::createSprite(glm::ivec2(32, 32), glm::vec2(1.0 / 20.0, 1.0), &spritesheet, &shaderProgram);
		sprite->setNumberAnimations(1);

		sprite->setAnimationSpeed(0, 8);
		sprite->addKeyframe(0, glm::vec2(11.f / 20.0f, 0.f));
		sprite->addKeyframe(0, glm::vec2(12.f / 20.0f, 0.f));
		sprite->addKeyframe(0, glm::vec2(13.f / 20.0f, 0.f));
		sprite->addKeyframe(0, glm::vec2(14.f / 20.0f, 0.f));

		sprite->changeAnimation(0);
		
	}
	else if (this->name == ROCK && this->type == ITEM) {
		spritesheet.loadFromFile("images/Roca.png", TEXTURE_PIXEL_FORMAT_RGBA);
		sprite = Sprite::createSprite(glm::ivec2(32, 32), glm::vec2(1.0, 1.0 / 3.0), &spritesheet, &shaderProgram);
		sprite->setNumberAnimations(1);

		sprite->setAnimationSpeed(0, 8);
		sprite->addKeyframe(0, glm::vec2(0.f, 1.f / 3.0f));
		sprite->addKeyframe(0, glm::vec2(0.f,2.f / 3.0f));
		sprite->addKeyframe(0, glm::vec2(0.f,3.f / 3.0f));
		
		sprite->changeAnimation(0);
	}


}


Object::~Object() {
	delete sprite;
}


void Object::update(int deltaTime)
{

	if (properties.find(IS_YOU) != properties.end()) {

		if (Game::instance().getSpecialKey(GLUT_KEY_RIGHT)) {
			this->pos.x += 1;
		}
		else if (Game::instance().getSpecialKey(GLUT_KEY_LEFT)) {
			this->pos.x -= 1;
		}

		else if (Game::instance().getSpecialKey(GLUT_KEY_UP)) {
			this->pos.y -= 1;
		}
		else if (Game::instance().getSpecialKey(GLUT_KEY_DOWN)) {
			this->pos.y += 1;
		}
	}

	sprite->update(deltaTime);
}


void Object::render()
{
	float offset_x = float(pos.x) * map->getTileSize().x;
	float offset_y = float(pos.y) * map->getTileSize().y;

	sprite->setPosition(glm::vec2(float(map->getOrigin().x + offset_x), float((map->getOrigin().y + offset_y))));
	sprite->render();
}


void Object::setPosition(int x, int y)
{
	this->pos = glm::ivec2(x,y);
}


void Object::addProperty(Property property) {
	properties.insert(property);

}

void Object::removeProperty(Property property) {
	properties.erase(property);
}
