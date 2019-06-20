#include "Button.h"
#include "ResourceManager.h";
#include "WindowSize.h"

Button::Button(string _texture) :texture(_texture)
{
	position = glm::vec2(200, 100);
	width = 190;
	height = 50;
	textureID
		= ResourceManager::getTexture(_texture).id;
	color.set(255, 255, 255, 255);
}

void Button::draw(SpriteBatch& spriteBatch) {
	const glm::vec4 uvRect(0.0f, 0.0f, 1.0f, 1.0f);
	glm::vec4 desctRect(position.x, position.y, width, height);
	spriteBatch.draw(desctRect, uvRect, textureID, 0.0f, color);
}

void Button::setColor(ColorRGBA _color)
{
	color = _color;
}

bool Button::click(glm::vec2 _position)
{
	return  ((_position.x > position.x)
		&& (_position.x < position.x + width))
		&& ((WINDOW_HEIGHT - _position.y > position.y)
		&& (WINDOW_HEIGHT - _position.y < position.y + height));
}

Button::~Button()
{
}
