#include "ScoreScreen.h"
#include "Game.h"
#include "MyScreens.h"
#include "WindowSize.h"
#include <iostream>
#include <algorithm>
#include <random>
using namespace std;

ScoreScreen::ScoreScreen(Window* window) :_window(window),
			btnGameClicked(false)
{
	_screenIndex = SCREEN_INDEX_Score;
}


ScoreScreen::~ScoreScreen()
{
}

void ScoreScreen::initGUI() {
}

void ScoreScreen::initSystem() {
	_program.compileShaders("Shaders/colorShaderVert.txt",
		"Shaders/colorShaderFrag.txt");
	_program.addAtribute("vertexPosition");
	_program.addAtribute("vertexColor");
	_program.addAtribute("vertexUV");
	_program.linkShader();
}

void ScoreScreen::destroy() {
	delete background;
	delete button;
	//delete _spriteFont;
	//delete _buttonFont;
}
void ScoreScreen::onExit() {}

void ScoreScreen::onEntry() {
	initSystem();

	_camera2D.init(_window->getScreenWidth(),
		_window->getScreenHeight());
	_camera2D.setPosition(glm::vec2(
		_window->getScreenWidth() / 2.0f,
		_window->getScreenHeight() / 2.0f));

	_spriteBatch.init();

	_hudBatch.init();

	_hudCamera.init(_window->getScreenWidth(),
		_window->getScreenHeight());
	_hudCamera.setPosition(
		glm::vec2(_window->getScreenWidth() / 2.0f,
			_window->getScreenHeight() / 2.0f));

	_spriteFont = new SpriteFont("Fonts/SNES Italic.ttf", 150);
	_buttonFont = new SpriteFont("Fonts/SNES Italic.ttf", fontSize / 3);
	buttonPosition = glm::vec2(WINDOW_WIDTH - 140, WINDOW_HEIGHT - 50);
	background = new Background("Textures/Final/menu.png");
	button = new Button("Textures/menu_button.png",glm::vec2(0,0), WINDOW_WIDTH, WINDOW_HEIGHT);
	button->setColor(ColorRGBA(0, 0, 0, 0));
	//initGUI();
}

void ScoreScreen::update() {
	_hudCamera.update();
	_camera2D.update();
	if (_game->_inputManager.isKeyDown(SDL_BUTTON_LEFT)) {
		if (!button->getClicked() 
			&& button->click(_game->_inputManager.getMouseCoords()))
		{
			button->SetClicked(true);
			_currentState = ScreenState::CHANGE_PREVIOUS;
		}
	}
	checkInput();
}

void ScoreScreen::checkInput() {
	SDL_Event event;
	while (SDL_PollEvent(&event)) {
		_game->onSDLEvent(event);
	}
}

void ScoreScreen::draw() {
	glClearDepth(1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	_program.use();
	glActiveTexture(GL_TEXTURE0);

	GLuint pLocation = _program.getUniformLocation("P");
	
	glm::mat4 cameraMatrix = _camera2D.getCameraMatrix();
	glUniformMatrix4fv(pLocation, 1, GL_FALSE, &(cameraMatrix[0][0]));

	GLuint imageLocation = _program.getUniformLocation("myImage");
	glUniform1i(imageLocation, 0);

	_spriteBatch.begin();
	
	background->draw(_spriteBatch);
	button->draw(_spriteBatch);

	_spriteBatch.end();
	_spriteBatch.renderBatch();

	drawHUD();
	glBindTexture(GL_TEXTURE_2D, 0);
	_program.unuse();
}

void  ScoreScreen::drawHUD() {
	GLuint pLocation =
		_program.getUniformLocation("P");

	glm::mat4 cameraMatrix = _hudCamera.getCameraMatrix();
	glUniformMatrix4fv(pLocation, 1, GL_FALSE, &(cameraMatrix[0][0]));

	char buffer[256];

	_hudBatch.begin();

	sprintf_s(buffer, "YA ME FUI LA BIKA G_G");
	_spriteFont->draw(_hudBatch, buffer,
		glm::vec2(WINDOW_WIDTH / 2 - fontSize, WINDOW_HEIGHT/2),
		glm::vec2(0.5), 0.0f, ColorRGBA(255, 255, 255, 255));

	_hudBatch.end();
	_hudBatch.renderBatch();
}

void ScoreScreen::build() {}

int ScoreScreen::getPreviousScreen() const {
	return SCREEN_INDEX_MENU;
}

int ScoreScreen::getNextScreen() const {
	return SCREEN_INDEX_MENU;
}