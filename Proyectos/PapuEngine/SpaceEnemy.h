#pragma once
#include "Agent.h"
#include "InputManager.h"
#include "Type.h"
using namespace std;

class SpaceEnemy:public Agent
{
private:
	int behaviour=0;
	enum AgentType type;
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
			type = blue;
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

	~SpaceEnemy();
};

