#pragma once
#include "IGameScreen.h"
#include "Window.h"
#include "GLS_Program.h"
#include "SpriteFont.h"
#include "Background.h"
#include "Button.h"
#include "Camera2D.h"
#include "SpriteBacth.h"
#include "SoundManager.h"

using namespace std;

class MenuScreen : public IGameScreen
{
private:
	Background* background = nullptr;
	Button* button = nullptr;

	Window* _window = nullptr;
	bool btnGameClicked;
	GLS_Program _program;
	SpriteBatch _spriteBatch;
	SpriteFont* _spriteFont;
	SpriteFont* _buttonFont;
	Camera2D _camera2D;
	//SoundManager* soundManager;
	int fontSize = 150;
public:
	MenuScreen(Window* window);
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
	~MenuScreen();
};

