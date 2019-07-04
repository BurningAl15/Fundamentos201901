#pragma once
#include "Agent.h"
#include "InputManager.h"
#include <SDL\SDL.h>
#include "Type.h"

using namespace std;

class MainCharacter:public Agent
{
private:
	InputManager* inputManager;
	float movementSpeed;
	enum AgentType type;
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

	enum AgentType GetType()
	{
		return type;
	}

	void SetType(int _type)
	{
		switch (_type)
		{
			default:
			case 0:
				type =blue;
				break;
			case 1:
				type = yellow;
				break;
			case 2:
				type = green;
				break;
			case 3:
				type = red;
				break;
		}
	}
	std::string getTexture();

	~MainCharacter();
};

