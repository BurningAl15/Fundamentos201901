#pragma once
#include "IGameScreen.h"
#include "Camera2D.h"
#include "GLS_Program.h"
#include "Window.h"
#include "SpriteBacth.h"
#include "GLTexture.h"
#include "Background.h"
#include "MainCharacter.h"
#include "SoundManager.h"
#include "SpaceEnemy.h"
#include "SpriteFont.h"
#include "Bullet.h"
#include "PowerUp.h"

class PlayScreen : public IGameScreen
{
private:
	Background* background;
	MainCharacter* player;
	GLS_Program _program;
	Camera2D _camera2D;
	Window* _window = nullptr;
	SpriteBatch _spriteBatch;
	SpriteBatch _hudBach;
	Camera2D _hudCamera;
	SoundManager* soundManager;
	SpriteFont* _timeFont;
	SpriteFont* _lifeFont;
	SpriteFont* _scoreFont;

	vector<SpaceEnemy*> enemies;
	vector<string> enemyPaths;
	string currentPlayerSprite="";
	int gameScore = 0;
	int timer = 0;
	int life = 3;
	int chainChecker = 0;

	//int enemyProductionDelay = 0;
	//int enemyProductionMaxDelay = 150;

	void drawHUD();
public:
	PlayScreen(Window* window);
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

	int TimeConverter(int _timer);
	~PlayScreen();
};

