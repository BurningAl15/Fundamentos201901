#include "Bullet.h"
#include "ResourceManager.h"
#include <SDL\SDL.h>
#include "WindowSize.h"

Bullet::Bullet(float agent_width,
	float agent_height,
	glm::vec2 position,
	std::string texture) 
	:Agent(agent_width, agent_height, position, texture)
{
}

Bullet::~Bullet()
{
}

void Bullet::update()
{
	_position.y += movementSpeed;
}

void Bullet::update_Enemy(float _newXPosition)
{}

std::string Bullet::getTexture() {
	return this->_texturePath;
}