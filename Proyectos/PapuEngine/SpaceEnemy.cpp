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

void SpaceEnemy::update() {
	switch (behaviour)
	{
	default:
	case 0:
		_position.y -= _speed;
		break;
	case 1:
		_position.y -= _speed;
		_position.x += _speed;
		break;
	case 2:
		_position.y -= _speed;
		_position.x -= _speed;
		break;
	case 3:
		//posX=0;
		_position.x += _speed;
		break;
	case 4:
		//posx=ScreenHeight
		_position.x -= _speed;
		break;
	}
}

void SpaceEnemy::update_Enemy(float _newXPosition)
{
}

std::string SpaceEnemy::getTexture() {
	return this->_texturePath;
}

SpaceEnemy::~SpaceEnemy()
{
}
