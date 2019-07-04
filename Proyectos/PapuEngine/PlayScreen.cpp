#include "PlayScreen.h"
#include "Game.h"
#include "MyScreens.h"
#include "WindowSize.h"
#include <random>
#include <ctime>
#include <iostream>
#include <algorithm>
#include <random>
#include "TexturesNameManager.h"
using namespace std;

PlayScreen::PlayScreen(Window* window):_window(window)
{
	_timeFont = new SpriteFont("Fonts/SNES Italic.ttf", 150);
	_lifeFont = new SpriteFont("Fonts/SNES Italic.ttf", 150);
	_scoreFont = new SpriteFont("Fonts/SNES Italic.ttf", 150);
	background = new Background(background1_PATH);

	_screenIndex = SCREEN_INDEX_GAME;
}


PlayScreen::~PlayScreen()
{
}

void PlayScreen::initGUI() {
	_hudBach.init();
	_hudCamera.init(_window->getScreenWidth(),
		_window->getScreenHeight());
	_hudCamera.setPosition(glm::vec2(
		_window->getScreenWidth() / 2.0f,
		_window->getScreenHeight() / 2.0f));
}

void PlayScreen::initSystem() {
	_program.compileShaders("Shaders/colorShaderVert.txt",
		"Shaders/colorShaderFrag.txt");
	_program.addAtribute("vertexPosition");
	_program.addAtribute("vertexColor");
	_program.addAtribute("vertexUV");
	_program.linkShader();
}

void PlayScreen::destroy() {
	delete background;
	delete _timeFont;
	delete _lifeFont;
	delete _scoreFont;
}

void PlayScreen::onExit() {}

void PlayScreen::onEntry() {
	initSystem();
	soundManager = new SoundManager("Sounds/Purple Planet Music - Atmospheric - Eventide.mp3",
		"Sounds/Shoot.wav","Sounds/collide.wav","Sounds/powerUp.wav", 
		"Sounds/bulletEnemyCollide.wav", "Sounds/ButtonPress.wav");

	_camera2D.init(_window->getScreenWidth(),
		_window->getScreenHeight());
	_camera2D.setPosition(glm::vec2(
		_window->getScreenWidth() / 2.0f,
		_window->getScreenHeight() / 2.0f));
	_spriteBatch.init();
	
	enemyPaths.push_back(blueEnemy_PATH);
	enemyPaths.push_back(yellowEnemy_PATH);
	enemyPaths.push_back(greenEnemy_PATH);
	enemyPaths.push_back(redEnemy_PATH);
	
	currentPlayerSprite = player_PATH;
	player = new MainCharacter(
		106,79,
		glm::vec2(50, WINDOW_HEIGHT/2),
		currentPlayerSprite,
		&_game->_inputManager);
	player->SetType(0);

	std::mt19937 randomEngine(time(nullptr));
	std::uniform_int_distribution<int> randomX(
		1, WINDOW_WIDTH
	);
	std::uniform_int_distribution<int> randomY(
		1, WINDOW_HEIGHT
	);
	std::uniform_int_distribution<int> speed(
		3,8
	);

	std::uniform_int_distribution<int> enemyType(
		0,3
	);
	int tempType;
	//Initial quantity of enemies
	for (int i = 0; i < 3; i++)
	{
		tempType = enemyType(randomEngine);

		enemies.push_back(new SpaceEnemy(
			50, 50,
			glm::vec2(WINDOW_WIDTH, randomY(randomEngine)),
			enemyPaths[tempType]));

		enemies[enemies.size() - 1]->SetType(tempType);
		enemies[enemies.size() - 1]->SetSpeed(speed(randomEngine));
		enemies[enemies.size() - 1]->SetYPos(randomY(randomEngine));
	}

	_game->_maxScore = 0;

	initGUI();
}

void PlayScreen::update() {
	_camera2D.update();

	player->update();
	std::mt19937 randomEngine(time(nullptr));

	std::uniform_int_distribution<int> randomX(
		1, WINDOW_WIDTH-20
	);

	std::uniform_int_distribution<int> randomY(
		1, WINDOW_HEIGHT
	);
	std::uniform_int_distribution<int> speed(
		3, 8
	);

	std::uniform_int_distribution<int> enemyType(
		0, 3
	);

	//TIMER
	timer++;

	if (chainChecker >= 5) {
		gameScore = gameScore * 2;
		chainChecker = 0;
	}

	int tempType;
	if (timer % 120==0)
	{
		//Initial quantity of enemies
		for (int i = 0; i < 3; i++)
		{
			tempType = enemyType(randomEngine);

			enemies.push_back(new SpaceEnemy(
				50, 50,
				glm::vec2(WINDOW_WIDTH, randomY(randomEngine)),
				enemyPaths[tempType]));

			enemies[enemies.size() - 1]->SetType(tempType);
			enemies[enemies.size() - 1]->SetSpeed(speed(randomEngine));
			enemies[enemies.size() - 1]->SetYPos(randomY(randomEngine));
		}
	}

	///
	player->changeTexture(currentPlayerSprite);
	///

	for (size_t i = 0; i < enemies.size(); i++)
	{
		enemies[i]->update();

		if (enemies[i]->getPosition().x < -100)
		{
			//enemies[i]->setPosition(glm::vec2(WINDOW_WIDTH, enemies[i]->getPosition().y));

			delete enemies[i];
			enemies[i] = enemies.back();
			enemies.pop_back();
		}
		else if (enemies[i]->collideWithAgent(player))
		{
			//delete enemies[i];
			//enemies[i] = enemies.back();
			//enemies.pop_back();
			enemies[i]->setPosition(glm::vec2(WINDOW_WIDTH, enemies[i]->getPosition().y));
			if (enemies[i]->GetType() == player->GetType())
			{
				chainChecker++;
				gameScore+=10;
				soundManager->PlaySFX1();
			}
			else if (enemies[i]->GetType() != player->GetType())
			{
				chainChecker = 0;
				if (life > 1)
				{
					life--;
					soundManager->PlaySFX2();
				}
				else
				{
					_game->_maxScore = gameScore;

					_currentState = ScreenState::CHANGE_NEXT;
				}
			}
		}
	}

	checkInput();
}

void PlayScreen::checkInput() {
	SDL_Event event;
	while (SDL_PollEvent(&event)) {
		_game->onSDLEvent(event);
		if (event.type == SDL_KEYDOWN)
		{
			switch (event.key.keysym.sym)
			{
			case SDLK_s:
			case SDLK_w:
			//soundManager->PlaySFX1();
					break;

			case SDLK_t:
				currentPlayerSprite =player_yellow_PATH;
				player->SetType(1);
				break;

			case SDLK_y:
				currentPlayerSprite = player_PATH;
				player->SetType(0);
				break;

			case SDLK_u:
				currentPlayerSprite = player_red_PATH;
				player->SetType(3);
				break;

			case SDLK_i:
				currentPlayerSprite = player_green_PATH;
				player->SetType(2);
				break;
			}
		}
	}
}

void PlayScreen::draw() {
	glClearDepth(1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	_program.use();
	glActiveTexture(GL_TEXTURE0);
	GLuint pLocation = _program.getUniformLocation("P");
	glm::mat4 cameraMatrix = _camera2D.getCameraMatrix();
	glUniformMatrix4fv(pLocation, 1, GL_FALSE, &(cameraMatrix[0][0]));

	GLuint imageLocation = _program.getUniformLocation("myImage");
	glUniform1i(imageLocation, 0);

	char buffer[256];

	_spriteBatch.begin();
	background->draw(_spriteBatch);

	sprintf(buffer, "Tiempo: %d", TimeConverter(timer));
	_timeFont->draw(_spriteBatch, buffer,
		glm::vec2(WINDOW_WIDTH / 4 - 150, WINDOW_HEIGHT - 100), glm::vec2(0.5), 5.0f,
		ColorRGBA(255, 255, 255, 255));

	sprintf(buffer, "Vidas: %d", life);
	_timeFont->draw(_spriteBatch, buffer,
		glm::vec2(WINDOW_WIDTH / 4 - 150, WINDOW_HEIGHT - 200), glm::vec2(0.5), 5.0f,
		ColorRGBA(255, 255, 255, 255));


	sprintf(buffer, "Puntaje: %d", gameScore);
	_scoreFont->draw(_spriteBatch, buffer,
		glm::vec2(3*WINDOW_WIDTH / 4 - 150, WINDOW_HEIGHT - 100), glm::vec2(0.5), 5.0f,
		ColorRGBA(255, 255, 255, 255));
	
	player->draw(_spriteBatch);

	for (size_t i = 0; i < enemies.size(); i++)
	{
		enemies[i]->draw(_spriteBatch);
	}

	_spriteBatch.end();
	_spriteBatch.renderBatch();
	drawHUD();
	glBindTexture(GL_TEXTURE_2D, 0);
	_program.unuse();
}

void PlayScreen::drawHUD() {
	GLuint pLocation = _program.getUniformLocation("P");
	glm::mat4 cameraMatrix = _camera2D.getCameraMatrix();
	glUniformMatrix4fv(pLocation, 1, GL_FALSE, &(cameraMatrix[0][0]));

	char buffer[256];
	_hudBach.begin();

	_hudBach.end();
	_hudBach.renderBatch();
}

int PlayScreen::TimeConverter(int _timer)
{
	int seconds = _timer / 60;

	return seconds;
}

void PlayScreen::build() {}

int PlayScreen::getPreviousScreen() const {
	return SCREEN_INDEX_MENU;
}

int PlayScreen::getNextScreen() const {
	//return SCREEN_INDEX_OVER;
	return SCREEN_INDEX_Score;
}