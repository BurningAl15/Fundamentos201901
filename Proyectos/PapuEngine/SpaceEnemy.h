#pragma once
#include "Agent.h"
#include "InputManager.h"

using namespace std;

class SpaceEnemy:public Agent
{
private:
	//InputManager* inputManager;
	//glm::vec2 position;
	//int id;
	bool isAlive;
	int behaviour=0;
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
	void SetYPos(float _yPos)
	{
		_position.y = _yPos;
	}
	void SetBehaviour(int _behaviour)
	{
		behaviour = _behaviour;
	}

	//int GetID() {
	//	return id;
	//}
	//void SetID(int _id) {
	//	id = _id;
	//}

	bool GetIsAlive() {
		return isAlive;
	}

	void SetIsAlive(bool _isAlive) {
		isAlive = _isAlive;
	}
	~SpaceEnemy();
};

