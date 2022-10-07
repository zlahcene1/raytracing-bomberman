/*
** EPITECH PROJECT, 2022
** B-YEP-400-PAR-4-1-indiestudio-tom.fuller
** File description:
** CreateGame
*/

#include "CreateGame.hpp"
#include <algorithm>
#include "Game.hpp"
#include "Utils.hpp"
#include "IA.hpp"

static const std::vector<std::vector<Input::Button>> keybinds {{
	{Input::Button::LEFT, Input::Button::UP, Input::Button::RIGHT, Input::Button::DOWN, Input::Button::SPACEBAR},
	{Input::Button::KEY_A, Input::Button::KEY_W, Input::Button::KEY_D, Input::Button::KEY_S, Input::Button::KEY_E},
	{Input::Button::KEY_J, Input::Button::KEY_I, Input::Button::KEY_L, Input::Button::KEY_K, Input::Button::KEY_O},
	{Input::Button::KEY_C, Input::Button::KEY_F, Input::Button::KEY_B, Input::Button::KEY_V, Input::Button::KEY_G}
}};

static const std::vector<Vector3> spawnPos {{
	{2.0, -11.0, 2.0},
	{2.0, -11.0, 24.0},
	{26.0, -11.0, 2.0},
	{26.0, -11.0, 24.0}
}};

Menu::CreateGame::CreateGame(std::vector<std::shared_ptr<Indie::IAudio>> &menuMusic,
 std::vector<std::shared_ptr<Indie::IAudio>> &menuAudio)
: _music(menuMusic), _audio(menuAudio), _raylib(std::make_unique<Raylib>()), _playerId(1), _botId(1)
{
	float widthCoef = static_cast<float>(ACT_BUTTON_WIDTH) / static_cast<float>(WIDTH);
	float heightCoef = static_cast<float>(ACT_BUTTON_HEIGHT) / static_cast<float>(HEIGHT);
	float pwidthCoef = static_cast<float>(PL_BUTTON_WIDTH) / static_cast<float>(WIDTH);
	float pheightCoef = static_cast<float>(PL_BUTTON_HEIGHT) / static_cast<float>(HEIGHT);

	_addPlayer = std::make_unique<Gui::Button>(0, 0, widthCoef, heightCoef, BLACK, RED, "Add Player", WHITE);
	_removePlayer = std::make_unique<Gui::Button>(0, 0, widthCoef, heightCoef, BLACK, RED, "Remove Player", WHITE);
	_addBot = std::make_unique<Gui::Button>(0, 0, widthCoef, heightCoef, BLACK, RED, "Add IA", WHITE);
	_removeBot = std::make_unique<Gui::Button>(0, 0, widthCoef, heightCoef, BLACK, RED, "Remove AI", WHITE);
	_play = std::make_unique<Gui::Button>(0, 0, pwidthCoef, pheightCoef, BLACK, RED, "PLAY", WHITE);
}

void Menu::CreateGame::startMenu()
{
	_raylib->showCursor();
}

bool Menu::CreateGame::closeMenu() const
{
	return _raylib->windowShouldClose();
}

void Menu::CreateGame::launchGame()
{
	std::vector<std::shared_ptr<IMovable>> players;
	std::shared_ptr<IMenu> game;
	int id = 0;

	for (unsigned int i = 0; i < _inputTypes.size(); i++) {
		if (_inputTypes[i]) {
			players.push_back(std::make_shared<Player>(_inputs[i]->getText(), spawnPos[i], keybinds[id], i));
			id += 1;
		} else {
			players.push_back(std::make_shared<Indie::IA>(spawnPos[i], _inputs[i]->getText(), i));
		}
	}
	game = std::make_shared<Game>(players, _music, _audio);
	game->run();
}

int Menu::CreateGame::run()
{
	startMenu();
	while (!closeMenu()) {
		update();
		if (event() == LAST_MENU) {
			launchGame();
			break;
		}
	}
	_raylib->hideCursor();
	return 1;
}

bool Menu::CreateGame::checkSelected(const Indie::CppVector2 &mousePos, std::unique_ptr<Gui::Button> &button)
{
	float posX = mousePos.getVectorX();
	float posY = mousePos.getVectorY();
	bool mouseOnButton = false;

	if ((posX > button->getPosX() && posX <= button->getWidth() + button->getPosX())
	&& (posY > button->getPosY() && posY < button->getHeight() + button->getPosY()))
		mouseOnButton = true;
	if (mouseOnButton && _raylib->isMouseButtonDown()) {
		_audio[0]->play();
		button->setState(Gui::PRESSED);
	} else if (mouseOnButton)
		button->setState(Gui::SELECTED);
	else
		button->setState(Gui::NOT_SELECTED);
	if (mouseOnButton && _raylib->isMouseButtonReleased())
		return true;
	return false;
}

void Menu::CreateGame::popInputBox(const bool &type)
{
	int i = 0;

	if (_inputTypes.size() == 0)
		return;
	if (std::find(_inputTypes.begin(), _inputTypes.end(), type) == _inputTypes.end())
		return;
	i = _inputTypes.size();
	for (; i >= 0 && _inputTypes[i] != type; i--);
	if (i >= 0) {
		_inputTypes.erase(_inputTypes.begin() + i);
		_inputs.erase(_inputs.begin() + i);
		if (type)
			_playerId -= 1;
		else
			_botId -= 1;
	}
}

void Menu::CreateGame::insertInputBox(const bool &type)
{
	long unsigned int i = 0;

	if ((_inputTypes.size() >= MAX_PLAYERS))
		return;
	if (!_inputs.size()) {
		_inputTypes.push_back(type);
		if (type) {
			_playerId += 1;
			_inputs.push_back(std::make_unique<Gui::InputBox>(10, "PLAYER"));
		} else {
			_botId += 1;
			_inputs.push_back(std::make_unique<Gui::InputBox>(10, "BOT"));
		}
	} else {
		if (type) {
			for (; i < _inputTypes.size() && _inputTypes[i] == true; i++);
			_inputTypes.insert(_inputTypes.begin() + i, type);
			_inputs.insert(_inputs.begin() + i, std::make_unique<Gui::InputBox>(10, "PLAYER"));
			_playerId += 1;
		} else {
			for (i = _inputTypes.size() - 1; i > 0 && _inputTypes[i] == false; i--);
			_inputTypes.insert(_inputTypes.begin() + i + 1, type);
			_inputs.insert(_inputs.begin() + i + 1, std::make_unique<Gui::InputBox>(10, "BOT"));
			_botId += 1;
		}
	}
}

Return_Status Menu::CreateGame::event()
{
	Input::Button key = _raylib->isKeyPressed();
	Indie::CppVector2 mousePos = _raylib->getMousePosition();
	bool isReleased = _raylib->isMouseButtonReleased();

	if (checkSelected(mousePos, _addPlayer))
		insertInputBox(true);
	if (checkSelected(mousePos, _removePlayer))
		popInputBox(true);
	if (checkSelected(mousePos, _addBot))
		insertInputBox(false);
	if (checkSelected(mousePos, _removeBot))
		popInputBox(false);
	for (auto &inputBox : _inputs) {
		if (_raylib->checkCollisionPointRec(mousePos, inputBox->getBounds()) && isReleased)
			inputBox->setState(Gui::SELECTED);
		else if (isReleased)
			inputBox->setState(Gui::NOT_SELECTED);
		if (inputBox->getState() == Gui::SELECTED && key >= Input::Button::KEY_A && key <= Input::Button::KEY_Z)
			inputBox->addCharacter(key);
		if (inputBox->getState() == Gui::SELECTED && key == Input::Button::DELETE)
			inputBox->removeCharacter();
	}
	if (checkSelected(mousePos, _play))
		return LAST_MENU;
	return NOTHING;
}

void Menu::CreateGame::update()
{
	int screenHeight = _raylib->getScreenHeight();
	int screenWidth = _raylib->getScreenWidth();
	int backgroundBorderX = screenWidth / 5.0;
	int backgroundBorderY = screenHeight / 7;
	int backgroundSizeY = screenHeight / 7 * 5;
	int backgroundSizeX = screenWidth / 5 * 3;
	int playersSizeX = backgroundSizeX / 3;
	int playersSizeY = backgroundSizeY * 0.7;
	int playersBorderX = screenWidth / 2 - playersSizeX / 2;
	int playersBorderY = backgroundBorderY * 1.3;
	int textFontSize = ACT_FONT_SIZE * screenWidth / WIDTH;
	int textSize = _raylib->measureText("Players", textFontSize);
	int leftPartX = backgroundBorderX + (((playersBorderX - backgroundBorderX) / 2) - (_addPlayer->getWidth() / 2));
	int rightPartX = playersBorderX + playersSizeX + (((playersBorderX - backgroundBorderX) / 2) - (_addPlayer->getWidth() / 2));
	int inputsX;
	int inputsSizeX = INPUT_WIDTH * screenWidth / WIDTH;
	int inputsSizeY = INPUT_HEIGHT * screenHeight / HEIGHT;
	int i = 1;

	_music[0]->update();
	_raylib->drawRectangle(0, 0, screenWidth, screenHeight, WHITE);
	_raylib->drawRectangle(backgroundBorderX, backgroundBorderY,
	backgroundSizeX, screenHeight / 7 * 5, GRAY);
	_raylib->drawRectangle(playersBorderX, playersBorderY, playersSizeX, playersSizeY, BLACK);
	_raylib->drawText("Players", playersBorderX + (playersSizeX / 2 - textSize / 2),
	playersBorderY * 1.1, textFontSize, WHITE);
	_addPlayer->resize(screenWidth, screenHeight);
	_addPlayer->reposition(leftPartX, backgroundBorderY * 1.8);
	_removePlayer->resize(screenWidth, screenHeight);
	_removePlayer->reposition(leftPartX, backgroundBorderY * 3);
	_addBot->resize(screenWidth, screenHeight);
	_addBot->reposition(rightPartX, backgroundBorderY * 1.8);
	_removeBot->resize(screenWidth, screenHeight);
	_removeBot->reposition(rightPartX, backgroundBorderY * 3);
	_play->resize(screenWidth, screenHeight);
	_play->reposition(screenWidth / 2 - _play->getWidth() / 2, backgroundBorderY + backgroundSizeY * 0.83);
	if (_inputs.size())
		inputsX = playersBorderX + playersSizeX / 2 - inputsSizeX / 2;
	for (auto &inputBox : _inputs) {
		inputBox->setPos(inputsX, playersBorderY + (playersBorderY / 3 * i) + playersBorderY / 4);
		inputBox->setSize(inputsSizeX, inputsSizeY);
		_raylib->drawInputBox(inputBox);
		i += 1;
	}
	_raylib->drawButton(_removeBot);
	_raylib->drawButton(_addBot);
	_raylib->drawButton(_removePlayer);
	_raylib->drawButton(_addPlayer);
	_raylib->drawButton(_play);
	_raylib->tick();
}

void Menu::CreateGame::drawUi()
{}

std::vector<std::shared_ptr<Indie::IAudio>> Menu::CreateGame::getSound() const
{
	return {};
}

std::vector<std::shared_ptr<Indie::IAudio>> Menu::CreateGame::getMusic() const
{
	return {};
}