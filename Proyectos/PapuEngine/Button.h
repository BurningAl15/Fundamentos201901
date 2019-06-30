#pragma once
#include "SpriteBacth.h"
#include "GLTexture.h"
#include <glm\glm.hpp>
#include <string>

using namespace std;

class Button
{
private:
	string texture;
	ColorRGBA color;
	int textureID;
	glm::vec2 position;
	float width;
	float height;
	bool clicked=false;
	
public:

	void SetClicked(bool _clicked) {
		clicked = _clicked;
	}

	bool getClicked()const {
		return clicked;
	}

	Button(string _texture);

	Button(string _texture,glm::vec2 _position,float _width,float _height);

	void draw(SpriteBatch& spriteBatch);
	void setColor(ColorRGBA _color);

	ColorRGBA getColor() const {
		return color;
	}

	bool click(glm::vec2 _position);

	~Button();
};

