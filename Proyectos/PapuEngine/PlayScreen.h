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
	SpriteFont* _spriteFont;
	SpriteFont* _scoreFont;

	vector<SpaceEnemy*> enemies;
	vector<Bullet*> bullets;
	vector<PowerUp*> powerUps;

	vector<float> positions;

	vector<string> bulletAnimationPaths;
	vector<string> playerAnimationPaths;
	vector<string> backgroundAnimationPaths;
	vector<string> powerUpAnimationPaths;

	int bulletFrame=0;
	int bulletAnimationSpeed=0;

	int playerFrame = 0;
	int playerAnimationSpeed = 0;

	int backgroundFrame = 0;
	int backgroundAnimationSpeed = 0;

	int powerUpFrame = 0;
	int powerUpAnimationSpeed = 0;

	int gameScore = 0;
	int bulletCounter = 0;
	int life = 10;
	int enemyProductionDelay = 0;
	int enemyProductionMaxDelay = 150;

	int powerUpProductionDelay = 0;
	int powerUpProductionMaxDelay = 500;

	int enemyBehaviour = 0;
	int enemyTypeHandler = 0;

	//int currentNumberOfEnemies=0;
	//int maxNumberOfEnemies = 10;
	//SpaceEnemy* enemy;
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
	~PlayScreen();
};

