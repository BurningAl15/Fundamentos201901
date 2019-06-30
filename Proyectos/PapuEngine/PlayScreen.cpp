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
	_spriteFont = new SpriteFont("Fonts/SNES Italic.ttf", 150);
	_scoreFont = new SpriteFont("Fonts/SNES Italic.ttf", 150);
	background = new Background(background2_PATH);
	background = new Background(background1_PATH);
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
	delete _spriteFont;
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
	
	player = new MainCharacter(
		106,79,
		glm::vec2(WINDOW_WIDTH/2, 100),
		/*player_PATH*/ player1_PATH,
		&_game->_inputManager);
	

	bulletAnimationPaths.push_back(projectile1_PATH);
	bulletAnimationPaths.push_back(projectile2_PATH);

	playerAnimationPaths.push_back(player1_PATH);
	playerAnimationPaths.push_back(player2_PATH);
	playerAnimationPaths.push_back(player3_PATH);

	backgroundAnimationPaths.push_back(background1_PATH);
	backgroundAnimationPaths.push_back(background2_PATH);

	powerUpAnimationPaths.push_back(powerUp1_PATH);
	powerUpAnimationPaths.push_back(powerUp2_PATH);
	powerUpAnimationPaths.push_back(powerUp3_PATH);

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

	positions.push_back(0.0f);
	positions.push_back(0.0f);

	for (int i = 0; i < 3; i++)
	{
		//currentNumberOfEnemies++;
		enemies.push_back(new SpaceEnemy(
			50, 50,
			glm::vec2(randomX(randomEngine), WINDOW_HEIGHT),
			asteroid1_PATH));
		enemies[enemies.size() - 1]->SetSpeed(speed(randomEngine));
	}

	_game->_maxScore = 0;

	initGUI();
}

void PlayScreen::update() {
	_camera2D.update();

	player->update();
	//player->changeTexture();
	//enemy->update();
	std::mt19937 randomEngine(time(nullptr));

	std::uniform_int_distribution<int> randomX(
		1, WINDOW_WIDTH-20
	);

	std::uniform_int_distribution<int> randomY(
		1, WINDOW_HEIGHT
	);
	std::uniform_int_distribution<int> randomDirection(
		-1, 1
	);

	#pragma region EnemySpeedZone 
		std::uniform_int_distribution<int> enemySpeed1(
			3, 5
		);
		std::uniform_int_distribution<int> enemySpeed2(
			5, 8
		);
		std::uniform_int_distribution<int> enemySpeed3(
			8, 11
		);
	#pragma endregion

	#pragma region EnemyWaveSize
		std::uniform_int_distribution<int> waveSize(
			3, 5
		);

		std::uniform_int_distribution<int> waveSize1(
			5, 7
		);
	#pragma endregion

	#pragma region EnemyBehaviours
		std::uniform_int_distribution<int> behaviour1(
			1,2
		);
		std::uniform_int_distribution<int> behaviour2(
			0, 2
		);
	#pragma endregion

	#pragma region EnemySize
	std::uniform_int_distribution<int> size1(
		70, 90
	);

	std::uniform_int_distribution<int> size2(
		50, 65
	);

	std::uniform_int_distribution<int> size3(
		30, 45
	);
	#pragma endregion


	enemyProductionDelay+=1;
	powerUpProductionDelay++;
	int tempWaveSize = 0;
	int tempEnemySize = 0;
	string currentEnemySprite = "";

	switch (enemyTypeHandler)
	{
	case 0:
		tempWaveSize = waveSize(randomEngine);
		tempEnemySize = size1(randomEngine);
		currentEnemySprite = asteroid4_PATH;
		break;
	case 1:
		tempWaveSize = waveSize(randomEngine);
		tempEnemySize = size2(randomEngine);
		currentEnemySprite = asteroid3_PATH;
		break;
	case 2:
		tempWaveSize = waveSize1(randomEngine);
		tempEnemySize = size3(randomEngine);
		currentEnemySprite = asteroid2_PATH;
		break;
	default:
	case 3:
		tempWaveSize = waveSize1(randomEngine);
		tempEnemySize = size3(randomEngine);
		currentEnemySprite = asteroid1_PATH;
		break;
	}

	float tempPosX=0;
	float tempPosY = 0;
	switch (enemyBehaviour)
	{
		default:
		case 0:
		case 1:
		case 2:
			tempPosX = randomX(randomEngine);
			tempPosY = WINDOW_HEIGHT;
			break;
		case 3:
			tempPosX = 0;
			tempPosY = randomY(randomEngine);
			break;
		case 4:
			tempPosX = WINDOW_WIDTH;
			tempPosY = randomY(randomEngine);
			break;
	}

	if (powerUpProductionDelay >= powerUpProductionMaxDelay)
	{
		for (int i = 0; i < 1; i++)
		{
			powerUps.push_back(new PowerUp(30, 30,
				glm::vec2(tempPosX, WINDOW_HEIGHT),
				powerUpAnimationPaths[0], 0));
			powerUps[powerUps.size() - 1]->SetSpeed(4);

			powerUpProductionDelay = 0;
		}
	}

	if(enemyProductionDelay >= enemyProductionMaxDelay) {
		for (int i = 0; i < tempWaveSize; i++)
		{
			enemies.push_back(new SpaceEnemy(
				tempEnemySize, tempEnemySize,
				glm::vec2(tempPosX, WINDOW_HEIGHT),
				currentEnemySprite));
			
			switch (enemyTypeHandler)
			{
			case 0:
				enemies[enemies.size() - 1]->SetSpeed(enemySpeed1(randomEngine));
				break;
			case 1:
				enemies[enemies.size() - 1]->SetSpeed(enemySpeed2(randomEngine));
				break;
			case 2:
			case 3:
				enemies[enemies.size() - 1]->SetSpeed(enemySpeed3(randomEngine));
				break;
			}
			if (enemyBehaviour >= 3)
				enemies[enemies.size() - 1]->SetYPos(randomY(randomEngine));
			enemies[enemies.size() - 1]->SetBehaviour(enemyBehaviour);
		}
		enemyProductionDelay = 0;
	}

	//TIMERS
	bulletAnimationSpeed++;
	playerAnimationSpeed++;
	backgroundAnimationSpeed++;
	powerUpAnimationSpeed++;

	if (bulletAnimationSpeed > 10)
	{
		bulletFrame++;
		bulletAnimationSpeed = 0;
	}

	if (playerAnimationSpeed > 10)
	{
		playerFrame++;
		playerAnimationSpeed = 0;
	}

	if (backgroundAnimationSpeed > 10)
	{
		backgroundFrame++;
		backgroundAnimationSpeed = 0;
	}

	if (powerUpAnimationSpeed > 10)
	{
		powerUpFrame++;
		powerUpAnimationSpeed = 0;
	}

	int tempPlayerFrame = 0;
	if (playerFrame % 3 == 0)
		tempPlayerFrame = 0;
	else if (playerFrame % 3 == 1)
		tempPlayerFrame = 1;	
	else if (playerFrame % 3 == 2)
		tempPlayerFrame = 2;
	
	player->changeTexture(playerAnimationPaths[tempPlayerFrame]);
	background->SetTexture(backgroundAnimationPaths[backgroundFrame % 2 != 1 ? 0 : 1]);

	for (size_t i = 0; i < bullets.size(); i++)
	{
		bullets[i]->update();

		bullets[i]->changeTexture(bulletAnimationPaths[bulletFrame%2!=1?0:1]);
		
		if (bullets[i]->getPosition().y >= WINDOW_HEIGHT)
		{
			delete bullets[i];
			bullets[i] = bullets.back();
			bullets.pop_back();
		}
	}

	for (size_t i = 0; i < enemies.size(); i++)
	{
		enemies[i]->update();

		if (enemies[i]->getPosition().y < -100)
		{
			enemies[i]->setPosition(glm::vec2(randomX(randomEngine),WINDOW_HEIGHT));

			//delete enemies[i];
			/*enemies[i] = enemies.back();
			enemies.pop_back();*/
		}
		else if (enemies[i]->getPosition().x < -100)
		{
			enemies[i]->setPosition(glm::vec2(WINDOW_WIDTH, enemies[i]->getPosition().y));
		}
		else if (enemies[i]->getPosition().x > WINDOW_WIDTH + 100)
		{
			enemies[i]->setPosition(glm::vec2(0, enemies[i]->getPosition().y));
		}
		else if (enemies[i]->collideWithAgent(player))
		{
			//delete enemies[i];
			//enemies[i] = enemies.back();
			//enemies.pop_back();
			enemies[i]->setPosition(glm::vec2(randomX(randomEngine), WINDOW_HEIGHT));

			if (life > 1)
			{
				life--;
				soundManager->PlaySFX2();
				//enemies[i]->setPosition(glm::vec2(randomX(randomEngine),WINDOW_HEIGHT));
			}
			else
			{
				_game->_maxScore = gameScore;

				_currentState = ScreenState::CHANGE_NEXT;
			}
		}

		for (int j = 0; j < bullets.size(); j++)
		{
			if (enemies[i]->collideWithAgent(bullets[j]))
			{
				delete bullets[j];
				soundManager->PlaySFX4();
				gameScore += 10;
				bullets[j] = bullets.back();
				bullets.pop_back();


				//delete enemies[i];
				enemies[i] = enemies.back();
				enemies.pop_back();
				break;
			}
		}
	}

	if (powerUps.size() > 0)
	{
		cout << powerUps.size() << endl;
		for (size_t i = 0; i < powerUps.size(); i++)
		{
			powerUps[i]->update();
			powerUps[i]->changeTexture(powerUpAnimationPaths[powerUpFrame % 3]);
			if (powerUps[i]->collideWithAgent(player))
			{
				life++;
				soundManager->PlaySFX3();
				delete powerUps[i];
				powerUps[i] = powerUps.back();
				powerUps.pop_back();
			}
		}
	}

	if (gameScore < 100)
	{
		player->SetSpeed(5.0f);
		enemyBehaviour = 0;
		enemyTypeHandler = 0;
	}
	else if (gameScore >= 100 && gameScore < 200)
	{
		player->SetSpeed(6.0f);
		enemyBehaviour = behaviour1(randomEngine);
		enemyTypeHandler = 1;
	}
	else if (gameScore >= 200 && gameScore < 300)
	{
		player->SetSpeed(7.0f);
		enemyBehaviour = behaviour2(randomEngine);
		enemyTypeHandler = 2;

	}
	else if (gameScore >= 300)
	{
		player->SetSpeed(8.0f);
		enemyBehaviour = behaviour2(randomEngine);
		enemyTypeHandler = 3;
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
			case SDLK_a:
			case SDLK_d:
			case SDLK_s:
			case SDLK_w:
			//soundManager->PlaySFX1();
					break;

			case SDLK_SPACE:
				soundManager->PlaySFX1();

				positions[0] = player->getPosition().x;
				positions[1] = player->getPosition().x + (player->GetWidthOrHeight().x-20);
				
				bullets.push_back(new Bullet(
					25, 25,
					glm::vec2(positions[bulletCounter%2!=0?0:1]
						, player->getPosition().y+player->GetWidthOrHeight().y/2.5f),
					projectile1_PATH));

				if (gameScore >= 0 && gameScore < 100)
					bullets[bullets.size() - 1]->SetSpeed(3.0f);
				else if (gameScore >= 100 && gameScore < 200)
					bullets[bullets.size() - 1]->SetSpeed(5.0f);
				else if (gameScore >= 200 && gameScore < 300)
					bullets[bullets.size() - 1]->SetSpeed(7.0f);
				else if (gameScore >= 300 && gameScore < 400)
					bullets[bullets.size() - 1]->SetSpeed(9.0f);
				else if (gameScore >= 400 && gameScore < 500)
					bullets[bullets.size() - 1]->SetSpeed(11.0f);
				else
					bullets[bullets.size() - 1]->SetSpeed(13.0f);

				bulletCounter++;
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

	sprintf(buffer, "Lifes: %d",life);
	_spriteFont->draw(_spriteBatch, buffer,
		glm::vec2(WINDOW_WIDTH / 3 - 150, WINDOW_HEIGHT - 100), glm::vec2(0.5), 5.0f,
		ColorRGBA(255, 255, 255, 255));
	
	sprintf(buffer, "Score: %d", gameScore);
	_scoreFont->draw(_spriteBatch, buffer,
		glm::vec2(2*WINDOW_WIDTH / 3 - 150, WINDOW_HEIGHT - 100), glm::vec2(0.5), 5.0f,
		ColorRGBA(255, 255, 255, 255));
	
	player->draw(_spriteBatch);

	for (size_t i = 0; i < enemies.size(); i++)
	{
		enemies[i]->draw(_spriteBatch);
	}

	for (size_t i = 0; i < bullets.size(); i++)
	{
		bullets[i]->draw(_spriteBatch);
	}

	for (size_t i = 0; i < powerUps.size(); i++)
	{
		powerUps[i]->draw(_spriteBatch);
	}

	//enemy->draw(_spriteBatch);
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

void PlayScreen::build() {}

int PlayScreen::getPreviousScreen() const {
	return SCREEN_INDEX_MENU;
}

int PlayScreen::getNextScreen() const {
	//return SCREEN_INDEX_OVER;
	return SCREEN_INDEX_Score;
}