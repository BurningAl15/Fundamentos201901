#include "SpaceEnemy.h"
#include "ResourceManager.h";
#include <SDL\SDL.h>
#include "WindowSize.h"
#include <random>
#include <ctime>
SpaceEnemy::SpaceEnemy(
	float agent_width, float agent_height,
	glm::vec2 position, 
	std::string texture)
	:Agent(agent_width, agent_height, position, texture)
{
	_speed = 0.5;
	//position= glm::vec2(randomX(randomEngine), randomY(randomEngine));
}

//SpaceEnemy::SpaceEnemy(
//	float agent_width,float agent_height,
//	glm::vec2 position,float speed,
//	std::string texture)
//	:Agent(agent_width, agent_height,position,speed, texture)
//{
//	
//	//position= glm::vec2(randomX(randomEngine), randomY(randomEngine));
//}

void SpaceEnemy::update() {}
void SpaceEnemy::update_Enemy(float _newXPosition)
{
	if (_position.y >= 0)
		_position.y -= 8.0f;
	else
	{
		_position.x = _newXPosition;
		_position.y = WINDOW_HEIGHT;
	}

}

std::string SpaceEnemy::getTexture() {
	return this->_texturePath;
}

SpaceEnemy::~SpaceEnemy()
{
}
