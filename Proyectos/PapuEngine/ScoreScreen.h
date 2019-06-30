#pragma once
#include "IGameScreen.h"
#include "Camera2D.h"
#include "GLS_Program.h"
#include "Window.h"
#include "SpriteBacth.h"
#include "GLTexture.h"
#include "Background.h"
#include "Button.h"
#include "SpriteFont.h"

using namespace std;

class ScoreScreen : public IGameScreen
{
private:
	Background* background = nullptr;
	Button* button = nullptr;
	Window* _window = nullptr;
	bool btnGameClicked;

	GLS_Program _program;
	SpriteBatch _spriteBatch;
	Camera2D _camera2D;
	SpriteFont* _spriteFont;
	SpriteFont* _buttonFont;

	Camera2D _hudCamera;
	SpriteBatch _hudBatch;

	int _score;
	vector<string> scores;
	int fontSize = 150;
	glm::vec2 buttonPosition;

	void drawHUD();

public:
	ScoreScreen(Window* window);

	virtual void build() override;
	virtual void destroy() override;
	virtual void onExit() override;
	virtual void onEntry() override;
	
	virtual void initGUI() override;
	virtual void draw() override;
	virtual void update()override;
	virtual void initSystem()override;
	virtual int getNextScreen() const override;
	virtual int getPreviousScreen() const override;
	virtual void checkInput() override;

	~ScoreScreen();
};

