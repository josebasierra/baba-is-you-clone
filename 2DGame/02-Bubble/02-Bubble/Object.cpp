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
	this->hasMoved = false;

	if (this->name == BABA && this->type == ITEM) {
		spritesheet.loadFromFile("images/baba_anim.png", TEXTURE_PIXEL_FORMAT_RGBA);
		sprite = Sprite::createSprite(glm::ivec2(32, 32), glm::vec2(1.0 / 20.0, 1.0), &spritesheet, &shaderProgram);
		sprite->setNumberAnimations(1);

		sprite->setAnimationSpeed(0, 8);
		sprite->addKeyframe(0, glm::vec2(11.f / 20.0f, 0.f));
		sprite->addKeyframe(0, glm::vec2(12.f / 20.0f, 0.f));
		sprite->addKeyframe(0, glm::vec2(13.f / 20.0f, 0.f));
		sprite->addKeyframe(0, glm::vec2(14.f / 20.0f, 0.f));
		
		
		/*sprite->setAnimationSpeed(LEFT, 8);
		sprite->addKeyframe(LEFT, glm::vec2(11.f / 20.0f, 0.f));
		sprite->addKeyframe(LEFT, glm::vec2(12.f / 20.0f, 0.f));
		sprite->addKeyframe(LEFT, glm::vec2(13.f / 20.0f, 0.f));
		sprite->addKeyframe(LEFT, glm::vec2(14.f / 20.0f, 0.f));

		sprite->setAnimationSpeed(RIGHT, 8);
		sprite->addKeyframe(RIGHT, glm::vec2(1.0f / 20.0f, 0.f));
		sprite->addKeyframe(RIGHT, glm::vec2(2.0f / 20.0f, 0.f));
		sprite->addKeyframe(RIGHT, glm::vec2(3.0f / 20.0f, 0.f));
		sprite->addKeyframe(RIGHT, glm::vec2(4.0f / 20.0f, 0.f));
		
		sprite->setAnimationSpeed(UP, 8);
		sprite->addKeyframe(UP, glm::vec2(6.0f / 20.0f, 0.f));
		sprite->addKeyframe(UP, glm::vec2(7.0f / 20.0f, 0.f));
		sprite->addKeyframe(UP, glm::vec2(8.0f / 20.0f, 0.f));
		sprite->addKeyframe(UP, glm::vec2(9.0f / 20.0f, 0.f));

		sprite->setAnimationSpeed(DOWN, 8);
		sprite->addKeyframe(DOWN, glm::vec2(15.0f / 20.0f, 0.f));
		sprite->addKeyframe(DOWN, glm::vec2(16.0f / 20.0f, 0.f));
		sprite->addKeyframe(DOWN, glm::vec2(17.0f / 20.0f, 0.f));
		sprite->addKeyframe(DOWN, glm::vec2(18.0f / 20.0f, 0.f));
		*/

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
	else if (this->name == BABA && this->type == NOUN) {
		spritesheet.loadFromFile("images/baba_text.png", TEXTURE_PIXEL_FORMAT_RGBA);
		sprite = Sprite::createSprite(glm::ivec2(32, 32), glm::vec2(1.0, 1.0 / 3.0), &spritesheet, &shaderProgram);
		sprite->setNumberAnimations(1);

		sprite->setAnimationSpeed(0, 8);
		sprite->addKeyframe(0, glm::vec2(0.f, 1.f / 3.0f));
		sprite->addKeyframe(0, glm::vec2(0.f, 2.f / 3.0f));
		sprite->addKeyframe(0, glm::vec2(0.f, 3.f / 3.0f));

		sprite->changeAnimation(0);
	}
	else if (this->name == IS && this->type == OPERATOR) {
		spritesheet.loadFromFile("images/is.png", TEXTURE_PIXEL_FORMAT_RGBA);
		sprite = Sprite::createSprite(glm::ivec2(32, 32), glm::vec2(1.0, 1.0 / 3.0), &spritesheet, &shaderProgram);
		sprite->setNumberAnimations(1);

		sprite->setAnimationSpeed(0, 4);
		sprite->addKeyframe(0, glm::vec2(0.f, 1.f / 3.0f));
		sprite->addKeyframe(0, glm::vec2(0.f, 2.f / 3.0f));
		sprite->addKeyframe(0, glm::vec2(0.f, 3.f / 3.0f));

		sprite->changeAnimation(0);
	}
	else if (this->name == YOU && this->type == PROPERTY) {
		spritesheet.loadFromFile("images/you.png", TEXTURE_PIXEL_FORMAT_RGBA);
		sprite = Sprite::createSprite(glm::ivec2(32, 32), glm::vec2(1.0, 1.0 / 3.0), &spritesheet, &shaderProgram);
		sprite->setNumberAnimations(1);

		sprite->setAnimationSpeed(0, 8);
		sprite->addKeyframe(0, glm::vec2(0.f, 1.f / 3.0f));
		sprite->addKeyframe(0, glm::vec2(0.f, 2.f / 3.0f));
		sprite->addKeyframe(0, glm::vec2(0.f, 3.f / 3.0f));

		sprite->changeAnimation(0);
	}
	else if (this->name == FLAG && this->type == NOUN) {
		spritesheet.loadFromFile("images/flag_text.png", TEXTURE_PIXEL_FORMAT_RGBA);
		sprite = Sprite::createSprite(glm::ivec2(32, 32), glm::vec2(1.0, 1.0 / 3.0), &spritesheet, &shaderProgram);
		sprite->setNumberAnimations(1);

		sprite->setAnimationSpeed(0, 8);
		sprite->addKeyframe(0, glm::vec2(0.f, 1.f / 3.0f));
		sprite->addKeyframe(0, glm::vec2(0.f, 2.f / 3.0f));
		sprite->addKeyframe(0, glm::vec2(0.f, 3.f / 3.0f));

		sprite->changeAnimation(0);
	}
	else if (this->name == WIN && this->type == PROPERTY) {
		spritesheet.loadFromFile("images/win.png", TEXTURE_PIXEL_FORMAT_RGBA);
		sprite = Sprite::createSprite(glm::ivec2(32, 32), glm::vec2(1.0, 1.0 / 3.0), &spritesheet, &shaderProgram);
		sprite->setNumberAnimations(1);

		sprite->setAnimationSpeed(0, 8);
		sprite->addKeyframe(0, glm::vec2(0.f, 1.f / 3.0f));
		sprite->addKeyframe(0, glm::vec2(0.f, 2.f / 3.0f));
		sprite->addKeyframe(0, glm::vec2(0.f, 3.f / 3.0f));

		sprite->changeAnimation(0);
	}
	else if (this->name == WALL && this->type == NOUN) {
		spritesheet.loadFromFile("images/wall_text.png", TEXTURE_PIXEL_FORMAT_RGBA);
		sprite = Sprite::createSprite(glm::ivec2(32, 32), glm::vec2(1.0, 1.0 / 3.0), &spritesheet, &shaderProgram);
		sprite->setNumberAnimations(1);

		sprite->setAnimationSpeed(0, 8);
		sprite->addKeyframe(0, glm::vec2(0.f, 1.f / 3.0f));
		sprite->addKeyframe(0, glm::vec2(0.f, 2.f / 3.0f));
		sprite->addKeyframe(0, glm::vec2(0.f, 3.f / 3.0f));

		sprite->changeAnimation(0);
	}
	else if (this->name == STOP && this->type == PROPERTY) {
		spritesheet.loadFromFile("images/stop.png", TEXTURE_PIXEL_FORMAT_RGBA);
		sprite = Sprite::createSprite(glm::ivec2(32, 32), glm::vec2(1.0, 1.0 / 3.0), &spritesheet, &shaderProgram);
		sprite->setNumberAnimations(1);

		sprite->setAnimationSpeed(0, 8);
		sprite->addKeyframe(0, glm::vec2(0.f, 1.f / 3.0f));
		sprite->addKeyframe(0, glm::vec2(0.f, 2.f / 3.0f));
		sprite->addKeyframe(0, glm::vec2(0.f, 3.f / 3.0f));

		sprite->changeAnimation(0);
	}
	else if (this->name == ROCK && this->type == NOUN) {
		spritesheet.loadFromFile("images/rock_text.png", TEXTURE_PIXEL_FORMAT_RGBA);
		sprite = Sprite::createSprite(glm::ivec2(32, 32), glm::vec2(1.0, 1.0 / 3.0), &spritesheet, &shaderProgram);
		sprite->setNumberAnimations(1);

		sprite->setAnimationSpeed(0, 8);
		sprite->addKeyframe(0, glm::vec2(0.f, 1.f / 3.0f));
		sprite->addKeyframe(0, glm::vec2(0.f, 2.f / 3.0f));
		sprite->addKeyframe(0, glm::vec2(0.f, 3.f / 3.0f));

		sprite->changeAnimation(0);
	}
	else if (this->name == PUSH && this->type == PROPERTY) {
		spritesheet.loadFromFile("images/push.png", TEXTURE_PIXEL_FORMAT_RGBA);
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


ObjectType Object::getType() {
	return this->type;
}

ObjectName Object::getName() {
	return this->name;
}

void Object::update(int deltaTime)
{
	sprite->update(deltaTime);
}


void Object::render()
{
	sprite->render();
}


void Object::refresh() {
	this->hasMoved = false;
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
		this->hasMoved = true;

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


bool Object::isWord() {
	return type == NOUN || type == OPERATOR || type == PROPERTY;
}


void Object::addProperty(ObjectName name) {
	if (name == PUSH) addProperty(IS_PUSH);
	else if (name == STOP) addProperty(IS_STOP);
	else if (name == YOU) addProperty(IS_YOU);
	else if (name == WIN) addProperty(IS_WIN);
}


void Object::addProperty(Property property) {
	properties.insert(property);
}

void Object::removeProperty(Property property) {
	properties.erase(property);
}


void Object::cleanProperties() {
	this->properties.clear();
}

bool Object::hasProperty(Property property) {
	return (properties.find(property) != properties.end());
}
