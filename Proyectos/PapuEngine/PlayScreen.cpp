#include "PlayScreen.h"
#include "Game.h"
#include "MyScreens.h"
#include "WindowSize.h"
#include <random>
#include <ctime>
#include <iostream>

using namespace std;

PlayScreen::PlayScreen(Window* window):_window(window)
{
	_spriteFont = new SpriteFont("Fonts/SNES Italic.ttf", 150);

	background = new Background("Textures/game.png");
	//player->changeTexture("Textures/Player.png");
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
}

void PlayScreen::onExit() {}

void PlayScreen::onEntry() {
	initSystem();
	soundManager = new SoundManager("Sounds/Purple Planet Music - Atmospheric - Eventide.mp3",
		"Sounds/jump.wav","Sounds/Impact.wav","Sounds/hit.wav");

	_camera2D.init(_window->getScreenWidth(),
		_window->getScreenHeight());
	_camera2D.setPosition(glm::vec2(
		_window->getScreenWidth() / 2.0f,
		_window->getScreenHeight() / 2.0f));
	_spriteBatch.init();
	player = new MainCharacter(
		106,79,
		glm::vec2(200, 200),
		"Textures/Player.png", 
		&_game->_inputManager);
	
	std::mt19937 randomEngine(time(nullptr));
	std::uniform_int_distribution<int> randomX(
		1, WINDOW_WIDTH
	);
	std::uniform_int_distribution<int> randomY(
		1, WINDOW_HEIGHT
	);

	for (int i = 0; i < 10; i++)
	{
		enemies.push_back(new SpaceEnemy(
			50,50,
			glm::vec2(randomX(randomEngine), randomY(randomEngine)),
			"Textures/piedra.png"));
	}
	
	initGUI();
}

void PlayScreen::update() {
	_camera2D.update();
	player->update();
	//enemy->update();
	std::mt19937 randomEngine(time(nullptr));
	std::uniform_int_distribution<int> randomX(
		1, WINDOW_WIDTH
	);
	
	for (size_t i = 0; i < enemies.size(); i++)
	{
		enemies[i]->update_Enemy(randomX(randomEngine));
		if (enemies[i]->collideWithAgent(player))
		{
			if (life > 0)
			{
				life--;
				soundManager->PlaySFX2();
				enemies[i]->setPosition(glm::vec2(enemies[i]->getPosition().x,WINDOW_HEIGHT));
			}
			else
			{
				_currentState = ScreenState::CHANGE_PREVIOUS;
			}
			//cout << "End Game"<<endl;
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
			case SDLK_a:
			case SDLK_d:
			case SDLK_s:
			case SDLK_w:
				
				soundManager->PlaySFX1();
				
					break;
			default:
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

	_spriteBatch.begin();;
	background->draw(_spriteBatch);

	sprintf(buffer, "Life: %d",life);
	_spriteFont->draw(_spriteBatch, buffer,
		glm::vec2(WINDOW_WIDTH / 2 - 150, WINDOW_HEIGHT - 100), glm::vec2(0.5), 5.0f,
		ColorRGBA(255, 255, 255, 255));
	
	player->draw(_spriteBatch);

	for (size_t i = 0; i < enemies.size(); i++)
	{
		enemies[i]->draw(_spriteBatch);
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
	return SCREEN_INDEX_OVER;
}
