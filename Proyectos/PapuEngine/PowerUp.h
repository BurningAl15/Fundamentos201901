#pragma once
#include "Agent.h"
#include "InputManager.h"
#include <SDL\SDL.h>

using namespace std;

class PowerUp:public Agent
{
private:
	float movementSpeed;
	int type;
public:
	PowerUp(float agent_width,
		float agent_height,
		glm::vec2 position,
		std::string texture,
		int _type);
	PowerUp(float agent_width,
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

	void SetType(int _type)
	{
		type = _type;
	}

	int GetType()
	{
		return type;
	}

	~PowerUp();
};

