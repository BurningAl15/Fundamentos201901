#include "PowerUp.h"
#include "ResourceManager.h";
#include <SDL\SDL.h>
#include "WindowSize.h"

PowerUp::PowerUp(float agent_width,
	float agent_height,
	glm::vec2 position,
	std::string texture,
	int _type)
	:Agent(agent_width, agent_height, position, texture)
{
	movementSpeed = 4.0f;
	type = _type;
}

PowerUp::~PowerUp()
{
}

void PowerUp::update()
{
	_position.y -= movementSpeed;
}

void PowerUp::update_Enemy(float _newXPosition)
{}

std::string PowerUp::getTexture() {
	return this->_texturePath;
}
