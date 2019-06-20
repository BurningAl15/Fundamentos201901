#include "Background.h"
#include "ResourceManager.h";
#include "WindowSize.h"

Background::Background(string _texture)
			:texture(_texture)
{
	textureID 
		= ResourceManager::getTexture(_texture).id;
	color.set(255, 255, 255, 255);
}

void Background::draw(SpriteBatch& spriteBatch) {
	const glm::vec4 uvRect(0.0f, 0.0f, 1.0f, 1.0f);
	glm::vec4 desctRect(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);
	spriteBatch.draw(desctRect, uvRect, textureID, 0.0f, color);
}

void Background::setColor(ColorRGBA _color) {
	color = _color;
}


Background::~Background()
{
}