#pragma once
#include "Agent.h"

class Bullet:public Agent
{
private:
	float movementSpeed;
public:
	Bullet(float agent_width,
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

	void SetSpeed(float _speed) {
		movementSpeed = _speed;
	}
	~Bullet();

};