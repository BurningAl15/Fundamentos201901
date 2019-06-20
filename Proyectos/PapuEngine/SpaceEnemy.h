#pragma once
#include "Agent.h"
#include "InputManager.h"

using namespace std;

class SpaceEnemy:public Agent
{
private:
	//InputManager* inputManager;
	//glm::vec2 position;
public:
	SpaceEnemy(float agent_width,
		float agent_height,
		glm::vec2 position,
		std::string texture);

	void update();
	void update_Enemy(float _newXPosition);
	void setPosition(glm::vec2 position) {
		this->_position = position;
	}
	void changeTexture(std::string texturePath) {
		this->_texturePath = texturePath;
	}
	std::string getTexture();
	void SetSpeed(float speed)
	{
		_speed = speed;
	}
	~SpaceEnemy();
};

