#pragma once
#include "ResourceManager.h"
#include "SpriteBatch.h"
#include "GLTexture.h"
#include <glm\glm.hpp>

const float TA_WIDTH = 60.0f;

class TA01 
{
private:
	glm::vec2 position;
	Color color;
	int textureID;
public:
	void init(glm::vec2 _position);
	void draw(SpriteBatch& spritebatch, int _spriteType);
	TA01();
	~TA01();
};

