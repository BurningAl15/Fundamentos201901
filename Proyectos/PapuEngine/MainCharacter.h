#pragma once
#include "Agent.h"
#include "InputManager.h"
#include <SDL\SDL.h>

using namespace std;

class MainCharacter:public Agent
{
private:
	InputManager* inputManager;
	float movementSpeed;
public:
	MainCharacter(float agent_width,
		float agent_height,
		glm::vec2 position,
		std::string texture);
	MainCharacter(float agent_width,
		float agent_height,
		glm::vec2 position,
		std::string texture,
		InputManager* _inputManager);
	void update();
	void update_Enemy(float _newXPosition);

	void setPosition(glm::vec2 position) {
		this->_position = position;
	}
	void changeTexture(std::string texturePath) {
		this->_texturePath = texturePath;
	}
	glm::vec2 GetWidthOrHeight() {
		return glm::vec2(_agent_width, _agent_height);
	}

	void SetSpeed(float _speed) {
		movementSpeed = _speed;
	}

	std::string getTexture();

	~MainCharacter();
};

