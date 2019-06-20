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

}

MainCharacter::MainCharacter(float agent_width,
	float agent_height,
	glm::vec2 position,
	std::string texture,
	InputManager* _inputManager)
	: Agent(agent_width, agent_height, position, texture)
{
	inputManager = _inputManager;
}

void MainCharacter::update()
{
	if (inputManager->isKeyDown(SDLK_w) || inputManager->isKeyDown(SDLK_UP))
	{
		if (_position.y <= WINDOW_HEIGHT)
			_position.y += 8.0f;
		else
			_position.y = 0;
	}
	if (inputManager->isKeyDown(SDLK_s) || inputManager->isKeyDown(SDLK_DOWN))
	{
		if (_position.y >= 0)
			_position.y -= 8.0f;
		else
			_position.y = WINDOW_HEIGHT;
	}
	if (inputManager->isKeyDown(SDLK_a) || inputManager->isKeyDown(SDLK_LEFT))
	{
		if (_position.x >= 0)
			_position.x -= 8.0f;
		else
			_position.x = WINDOW_WIDTH;
	}
	if (inputManager->isKeyDown(SDLK_d) || inputManager->isKeyDown(SDLK_RIGHT))
	{
		if (_position.x <= WINDOW_WIDTH)
			_position.x += 8.0f;
		else
			_position.x = 0;
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
