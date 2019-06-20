#pragma once
#include "Agent.h"
#include "InputManager.h"

using namespace std;

class MainCharacter:public Agent
{
private:
	InputManager* inputManager;
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
	std::string getTexture();

	~MainCharacter();
};

