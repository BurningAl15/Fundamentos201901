#include "MainCharacter.h"
#include "ResourceManager.h";
#include <SDL\SDL.h>
#include "WindowSize.h"

MainCharacter::MainCharacter(float agent_width,
	float agent_height,
	glm::vec2 position,
	std::string texture)
	:Agent(agent_width,agent_height,position,texture)
{
	movementSpeed = 5.0f;
}

MainCharacter::MainCharacter(float agent_width,
	float agent_height,
	glm::vec2 position,
	std::string texture,
	InputManager* _inputManager)
	: Agent(agent_width, agent_height, position, texture)
{
	inputManager = _inputManager;
	movementSpeed = 4.0f;
}

void MainCharacter::update()
{
	if (inputManager->isKeyDown(SDLK_w) || inputManager->isKeyDown(SDLK_UP))
	{
		if (_position.y <= WINDOW_HEIGHT)
			_position.y += movementSpeed;
		else
			_position.y = 0;
	}
	if (inputManager->isKeyDown(SDLK_s) || inputManager->isKeyDown(SDLK_DOWN))
	{
		if (_position.y >= 0)
			_position.y -= movementSpeed;
		else
			_position.y = WINDOW_HEIGHT;
	}
}
void MainCharacter::update_Enemy(float _newXPosition)
{}
std::string MainCharacter::getTexture(){
	return this->_texturePath;
}

MainCharacter::~MainCharacter()
{
}
