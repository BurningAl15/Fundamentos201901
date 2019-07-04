#include "MenuScreen.h"
#include "MyScreens.h"
#include "Game.h"
#include <iostream>
#include "WindowSize.h"

using namespace std;

MenuScreen::MenuScreen(Window* window):
	_window(window), btnGameClicked(false)
{
	_screenIndex = SCREEN_INDEX_MENU;
}

void MenuScreen::initGUI() {
	_spriteFont = new SpriteFont("Fonts/SNES Italic.ttf", fontSize);
	_nameFont = new SpriteFont("Fonts/SNES Italic.ttf", fontSize);
	//_buttonFont = new SpriteFont("Fonts/SNES Italic.ttf", fontSize/3);

	background = new Background("Textures/Final/menu.png");
	//button = new Button("Textures/menu_button.png");
	button = new Button("Textures/menu_button.png",glm::vec2(0,0),WINDOW_WIDTH, WINDOW_HEIGHT);
	button->setColor(ColorRGBA(0, 0, 0, 0));
}

void MenuScreen::initSystem() {
	_program.compileShaders("Shaders/colorShaderVert.txt",
							"Shaders/colorShaderFrag.txt");
	_program.addAtribute("vertexPosition");
	_program.addAtribute("vertexColor");
	_program.addAtribute("vertexUV");
	_program.linkShader();
}

void MenuScreen::destroy() {
	delete background;
	delete button;
	delete _spriteFont;
	delete _nameFont;
	//delete _buttonFont;
	//delete soundManager;
}

void MenuScreen::onExit() {}

void MenuScreen::onEntry() {
	initSystem();
	//soundManager = new SoundManager("Sounds/Purple Planet Music - Atmospheric - Midnight Bell.mp3");

	_camera2D.init(_window->getScreenWidth(), 
					_window->getScreenHeight());
	_camera2D.setPosition(glm::vec2(
		_window->getScreenWidth() / 2.0f,
		_window->getScreenHeight() / 2.0f));
	
	_spriteBatch.init();
	initGUI();
}

void MenuScreen::update() {
	_camera2D.update();
	if (_game->_inputManager.isKeyDown(SDL_BUTTON_LEFT)) {
		if (!button->getClicked() 
			&& button->click(_game->_inputManager.getMouseCoords()))
		{
			button->SetClicked(true);
			_currentState = ScreenState::CHANGE_NEXT;
		}
	}
	checkInput();
}

void MenuScreen::checkInput() {
	SDL_Event event;
	while (SDL_PollEvent(&event)) {
		_game->onSDLEvent(event);
	}
}

void MenuScreen::draw() {
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

	char buffer[256];
	_spriteBatch.begin();

	sprintf(buffer, "Bica 4 life G_G");
	_spriteFont->draw(_spriteBatch, buffer,
		glm::vec2(WINDOW_WIDTH/2- fontSize, WINDOW_HEIGHT-100), glm::vec2(0.5), 5.0f,
		ColorRGBA(255,255,255, 255));
	
	sprintf(buffer, "Aldhair Vera");
	_nameFont->draw(_spriteBatch, buffer,
		glm::vec2(WINDOW_WIDTH / 2 - fontSize, WINDOW_HEIGHT - 200), glm::vec2(0.5), 5.0f,
		ColorRGBA(255, 255, 255, 255));

	//sprintf(buffer, "Start");
	//_buttonFont->draw(_spriteBatch, buffer,
	//	glm::vec2(270, 110), glm::vec2(0.5), 6.0f,
	//	ColorRGBA(0, 0, 0, 255));

	_spriteBatch.end();
	_spriteBatch.renderBatch();

	glBindTexture(GL_TEXTURE_2D, 0);
	_program.unuse();
}

void MenuScreen::build() {}

int MenuScreen::getPreviousScreen() const {
	return SCREEN_INDEX_NO_SCREEN;
}

int MenuScreen::getNextScreen() const {
	return SCREEN_INDEX_GAME;
}

MenuScreen::~MenuScreen()
{
}
