#include "TA01.h"


TA01::TA01()
{
}

void TA01::init(glm::vec2 _position)
{
	position = _position;
	color.r = 255;
	color.g = 255;
	color.b = 255;
	color.a = 255;
}

void TA01::draw(SpriteBatch& spritebatch,int _spriteType) {
	
	//static int textureID;

	switch (_spriteType)
	{
	case 0:
		textureID = ResourceManager::getTexture("Textures/Bullet.png").id;
		
		break;
	case 1:
		textureID = ResourceManager::getTexture("Textures/Drop.png").id;

		break;
	case 2:
		textureID = ResourceManager::getTexture("Textures/Gradient.png").id;

		break;
	case 3:
		textureID = ResourceManager::getTexture("Textures/Ship.png").id;

		break;
	}
	const glm::vec4 uvRect(0.0f, 0.0f, 1.0f, 1.0f);
	glm::vec4 destRect(position.x, position.y, TA_WIDTH, TA_WIDTH);
	spritebatch.draw(destRect, uvRect, textureID, 0.0f, color);
}


TA01::~TA01()
{
}
