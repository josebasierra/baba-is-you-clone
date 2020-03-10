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
	this->pos = ivec2(0, 0);

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
	else if (this->name == WALL && this->type == ITEM) {
		spritesheet.loadFromFile("images/wall.png", TEXTURE_PIXEL_FORMAT_RGBA);
		sprite = Sprite::createSprite(glm::ivec2(32, 32), glm::vec2(1.0, 1.0 / 3.0), &spritesheet, &shaderProgram);
		sprite->setNumberAnimations(1);

		sprite->setAnimationSpeed(0, 8);
		sprite->addKeyframe(0, glm::vec2(0.f, 1.f / 3.0f)); //habria que hacerlo mas bonito
		/*sprite->addKeyframe(0, glm::vec2(0.f, 2.f / 3.0f));
		sprite->addKeyframe(0, glm::vec2(0.f, 3.f / 3.0f)); */

		sprite->changeAnimation(0);
	}
	else if (this->name == FLAG && this->type == ITEM) {
		spritesheet.loadFromFile("images/flag.png", TEXTURE_PIXEL_FORMAT_RGBA);
		sprite = Sprite::createSprite(glm::ivec2(32, 32), glm::vec2(1.0, 1.0 / 3.0), &spritesheet, &shaderProgram);
		sprite->setNumberAnimations(1);

		sprite->setAnimationSpeed(0, 8);
		sprite->addKeyframe(0, glm::vec2(0.f, 1.f / 3.0f)); 
		sprite->addKeyframe(0, glm::vec2(0.f, 2.f / 3.0f));
		sprite->addKeyframe(0, glm::vec2(0.f, 3.f / 3.0f)); 

		sprite->changeAnimation(0);
	}
}

Object:: ~Object() {
	delete sprite;
}



void Object::update(int deltaTime)
{
	sprite->update(deltaTime);
}


void Object::render()
{
	sprite->render();
}


void Object::updateTurn() {
	if (properties.find(IS_YOU) != properties.end()) {

		if (Game::instance().getSpecialKey(GLUT_KEY_RIGHT)) {
			moveTo(this->pos + ivec2(1, 0));
		}
		else if (Game::instance().getSpecialKey(GLUT_KEY_LEFT)) {
			moveTo(this->pos + ivec2(-1, 0));
		}

		else if (Game::instance().getSpecialKey(GLUT_KEY_UP)) {
			moveTo(this->pos + ivec2(0, -1));
		}
		else if (Game::instance().getSpecialKey(GLUT_KEY_DOWN)) {
			moveTo(this->pos + ivec2(0, 1));
		}
	}
}

bool Object::moveTo(ivec2 pos) {

	if (map->move(this, this->pos, pos)) {
		this->pos = pos;

		//compute and update sprite position only when object moves
		float offset_x = float(pos.x) * map->getTileSize().x;
		float offset_y = float(pos.y) * map->getTileSize().y;
		sprite->setPosition(glm::vec2(float(map->getOrigin().x + offset_x), float((map->getOrigin().y + offset_y))));

		return true;
	}
	
	return false;
}


bool Object::moveTo(int x, int y) {
	return moveTo(ivec2(x, y));
}

bool Object::setPos(int x, int y) {
	ivec2 pos = ivec2(x, y);
	map->add(this, pos);
	this->pos = pos;

	//compute and update sprite position only when object moves
	float offset_x = float(pos.x) * map->getTileSize().x;
	float offset_y = float(pos.y) * map->getTileSize().y;
	sprite->setPosition(glm::vec2(float(map->getOrigin().x + offset_x), float((map->getOrigin().y + offset_y))));

	return true; //temporal
}


void Object::addProperty(Property property) {
	properties.insert(property);

}

void Object::removeProperty(Property property) {
	properties.erase(property);
}

bool Object::hasProperty(Property property) {
	return (properties.find(property) != properties.end());
}
