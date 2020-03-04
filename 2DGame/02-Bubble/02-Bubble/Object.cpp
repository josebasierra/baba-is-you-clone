#include "Object.h"
#include <cmath>
#include <iostream>
#include <GL/glew.h>
#include <GL/glut.h>
#include "Game.h"


enum PlayerAnims
{
	STAND_LEFT, STAND_RIGHT, MOVE_LEFT, MOVE_RIGHT
};

Object::Object(Map* map, ShaderProgram &shaderProgram, ObjectType type, ObjectName name) {
	this->name = name;
	this->type = type;
	
	if (this->name == BABA && this->type == ITEM) {
		spritesheet.loadFromFile("images/baba_anim.png", TEXTURE_PIXEL_FORMAT_RGBA);
		sprite = Sprite::createSprite(glm::ivec2(32, 32), glm::vec2(1.0 / 20.0, 1.0), &spritesheet, &shaderProgram);
		sprite->setNumberAnimations(4);

		sprite->setAnimationSpeed(STAND_LEFT, 8);
		sprite->addKeyframe(STAND_LEFT, glm::vec2(10.f / 20.0f, 0.f));

		sprite->setAnimationSpeed(STAND_RIGHT, 8);
		sprite->addKeyframe(STAND_RIGHT, glm::vec2(0.f, 0.f));

		sprite->setAnimationSpeed(MOVE_LEFT, 8);
		sprite->addKeyframe(MOVE_LEFT, glm::vec2(11.f / 20.0f, 0.f));
		sprite->addKeyframe(MOVE_LEFT, glm::vec2(12.f / 20.0f, 0.f));
		sprite->addKeyframe(MOVE_LEFT, glm::vec2(13.f / 20.0f, 0.f));
		sprite->addKeyframe(MOVE_LEFT, glm::vec2(14.f / 20.0f, 0.f));

		sprite->setAnimationSpeed(MOVE_RIGHT, 8);
		sprite->addKeyframe(MOVE_RIGHT, glm::vec2(1.0f / 20.0f, 0.f));
		sprite->addKeyframe(MOVE_RIGHT, glm::vec2(2.0f / 20.0f, 0.f));
		sprite->addKeyframe(MOVE_RIGHT, glm::vec2(3.0f / 20.0f, 0.f));
		sprite->addKeyframe(MOVE_RIGHT, glm::vec2(4.0f / 20.0f, 0.f));

		sprite->changeAnimation(0);
		
	}
	if (this->name == ROCK && this->type == ITEM) {
		spritesheet.loadFromFile("images/Roca.png", TEXTURE_PIXEL_FORMAT_RGBA);
		sprite = Sprite::createSprite(glm::ivec2(32, 32), glm::vec2(1.0, 1.0 / 3.0), &spritesheet, &shaderProgram);
		sprite->setNumberAnimations(1);

		sprite->setAnimationSpeed(MOVE_LEFT, 8);
		sprite->addKeyframe(MOVE_LEFT, glm::vec2(0.f, 1.f / 3.0f));
		sprite->addKeyframe(MOVE_LEFT, glm::vec2(0.f,2.f / 3.0f));
		sprite->addKeyframe(MOVE_LEFT, glm::vec2(0.f,3.f / 3.0f));
		
		sprite->changeAnimation(0);
	}

	
	
}

Object::~Object() {
	delete sprite;
}

void Object::update(int deltaTime)
{
	sprite->update(deltaTime);
	if (Game::instance().getSpecialKey(GLUT_KEY_LEFT))
	{
		if (sprite->animation() != MOVE_LEFT)
			sprite->changeAnimation(MOVE_LEFT);
		pos.x -= 1;

	}
	else if (Game::instance().getSpecialKey(GLUT_KEY_RIGHT))
	{
		if (sprite->animation() != MOVE_RIGHT)
			sprite->changeAnimation(MOVE_RIGHT);
		pos.x += 1;

	}
	else
	{
		if (sprite->animation() == MOVE_LEFT)
			sprite->changeAnimation(STAND_LEFT);
		else if (sprite->animation() == MOVE_RIGHT)
			sprite->changeAnimation(STAND_RIGHT);
	}

}

void Object::render()
{
	float offset_x = pos.x * map->get_tileSize.x;
	float offset_y = pos.y * map->get_tileSize.y;

	sprite->setPosition(glm::vec2(float(map->get_origin.x + offset_x), float((map->get_origin.y + offset_y))));
	sprite->render();
}

void Object::setPosition(int x, int y)
{

	this->pos = glm::ivec2(x,y);
}
