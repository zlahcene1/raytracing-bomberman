/*
** EPITECH PROJECT, 2022
** indie
** File description:
** MainMenu
*/

#include "Utils.hpp"
#include "MainMenu.hpp"
#include "Raylib.hpp"
#include "Game.hpp"
#include "Settings.hpp"
#include "Map.hpp"
#include "CreateGame.hpp"
#include "Pause.hpp"
#include <iostream>
#include <fstream>
#include <cstdint>
#include <filesystem>
#include "Save.hpp"

MainMenu::MainMenu()
: _raylib(std::make_unique<Raylib>()), _cursIdx(0), _savedMap(false)
{
	if (std::filesystem::exists("../save.txt"))
		_savedMap = true;
	float widthCoef = static_cast<float>(BUTTON_WIDTH) / static_cast<float>(WIDTH);
	float heightCoef = static_cast<float>(BUTTON_HEIGHT) / static_cast<float>(HEIGHT);

	_buttons.push_back(std::make_unique<Gui::Button>(0, 0, widthCoef, heightCoef, BLACK, RED, "Continue", WHITE));
	if (!_savedMap)
		_buttons[0]->setState(Gui::ButtonState::DISABLED);
	_buttons.push_back(std::make_unique<Gui::Button>(0, 0, widthCoef, heightCoef, BLACK, RED, "New Game", WHITE));
	_buttons.push_back(std::make_unique<Gui::Button>(0, 0, widthCoef, heightCoef, BLACK, RED, "Settings", WHITE));
	_buttons.push_back(std::make_unique<Gui::Button>(0, 0, widthCoef, heightCoef, BLACK, RED, "Exit", WHITE));
}

bool MainMenu::closeMenu() const
{
	return _raylib->windowShouldClose();
}

void MainMenu::loadingScreen()
{
    int screenWidth = _raylib->getScreenWidth();
    int screenHeight = _raylib->getScreenHeight();
    int logoPositionX = screenWidth / 2 - 128;
    int logoPositionY = screenHeight / 2 - 128;
    int framesCounter = 0;
    int lettersCount = 0;
    int topSideRecWidth = 16;
    int leftSideRecHeight = 16;
    int bottomSideRecWidth = 16;
    int rightSideRecHeight = 16;
    int state = 0;
    int alpha = 1;
	std::string game = "bomberman";

    while (!_raylib->windowShouldClose()) {
		screenWidth = _raylib->getScreenWidth();
    	screenHeight = _raylib->getScreenHeight();
        if (state == 0) {
            framesCounter++;
            if (framesCounter == 120) {
                state = 1;
                framesCounter = 0;
            }
        } else if (state == 1) {
            topSideRecWidth += 4;
            leftSideRecHeight += 4;
            if (topSideRecWidth == 256)
				state = 2;
        } else if (state == 2) {
            bottomSideRecWidth += 4;
            rightSideRecHeight += 4;
            if (bottomSideRecWidth == 256)
				state = 3;
		} else if (state == 3) {
            framesCounter++;
            if (framesCounter / 12) {
                lettersCount++;
                framesCounter = 0;
			}
			if (lettersCount >= 10) {
                alpha -= 0.02f;
				if (alpha <= 0.0f) {
                    alpha = 0.0f;
                    state = 4;
                }
            }
        } else if (state == 4 && IsKeyPressed(KEY_SPACE))
			break;
        _raylib->beginDrawing();
		_raylib->clearBackground();
		if (state == 0) {
			if ((framesCounter/15) % 2)
				_raylib->drawRectangle(logoPositionX, logoPositionY, 16, 16, RED);
		} else if (state == 1) {
			_raylib->drawRectangle(logoPositionX, logoPositionY, topSideRecWidth, 16, RED);
			_raylib->drawRectangle(logoPositionX, logoPositionY, 16, leftSideRecHeight, RED);
		} else if (state == 2) {
			_raylib->drawRectangle(logoPositionX, logoPositionY, topSideRecWidth, 16, RED);
			_raylib->drawRectangle(logoPositionX, logoPositionY, 16, leftSideRecHeight, RED);
			_raylib->drawRectangle(logoPositionX + 240, logoPositionY, 16, rightSideRecHeight, RED);
			_raylib->drawRectangle(logoPositionX, logoPositionY + 240, bottomSideRecWidth, 16, RED);
		} else if (state == 3) {
			_raylib->drawRectangle(logoPositionX, logoPositionY, topSideRecWidth, 16, Color({230, 41, 55, 1}));
			_raylib->drawRectangle(logoPositionX, logoPositionY + 16, 16, leftSideRecHeight - 32, Color({230, 41, 55, 1}));
			_raylib->drawRectangle(logoPositionX + 240, logoPositionY + 16, 16, rightSideRecHeight - 32, Color({230, 41, 55, 1}));
			_raylib->drawRectangle(logoPositionX, logoPositionY + 240, bottomSideRecWidth, 16, Color({230, 41, 55, 1}));
			_raylib->drawRectangle(screenHeight /2 - 112, screenHeight /2 - 112, 224, 224, Color({230, 41, 55, 1}));
			_raylib->drawText(game.substr(0, lettersCount), screenWidth / 2 - 80, screenHeight / 2 + 80, 36, RED);
		} else if (state == 4)
			_raylib->drawText("[SPACE] continue", WIDTH / 2 - 100, HEIGHT / 2, 20, RED);
        _raylib->endDrawing();
    }
    return;
}

int MainMenu::run()
{
	Return_Status status = NOTHING;
	startMenu();
	loadingScreen();
	_menuMusic[0]->play();
	while (!closeMenu()) {
		update();
		status = event();
		if (status == LAST_MENU)
			break;
	}
	CloseWindow();
	return 0;
}

std::shared_ptr<IMenu> MainMenu::getptr()
{
	return shared_from_this();
}

void MainMenu::startMenu()
{
    _raylib->initWindow(WIDTH, HEIGHT, 60, "Indie");
	_menuActions.push_back(std::make_shared<Indie::CppSound>("../assets/audio/sounds/button_actions.wav", 0.5));
	_menuMusic.push_back(std::make_shared<Indie::CppMusic>("../assets/audio/music/bouncy.mp3", 0.5));
	_raylib->hideCursor();
}

void MainMenu::update()
{
	drawUi();
	_raylib->tick();
}

Return_Status MainMenu::event()
{
    Input::Button key = _raylib->isKeyPressed();
	bool released = _raylib->isKeyReleased(Input::Button::ENTER);

	Gui::update_buttons(_buttons, _cursIdx);
	if (key == Input::Button::ENTER)
		_buttons[_cursIdx]->setState(Gui::PRESSED);
	if (_raylib->isKeyReleased(Input::Button::ENTER))
		_buttons[_cursIdx]->setState(Gui::SELECTED);
	if (released && _cursIdx == 0) {
		Indie::Save save;
		std::vector<std::shared_ptr<IMovable>> players;
		std::vector<std::string> map;
		save.loadFile(players, map);
		std::shared_ptr<Game> game = std::make_shared<Game>(players, _menuMusic, _menuActions, map);
		if (game->run() == 1)
			return LAST_MENU;
		if (!std::filesystem::exists("../save.txt"))
			_buttons[0]->setState(Gui::ButtonState::DISABLED);
    }
    if (released && _cursIdx == 1) {
		std::unique_ptr<Menu::CreateGame> game = std::make_unique<Menu::CreateGame>(_menuMusic, _menuActions);
		if (game->run() == 1)
			return LAST_MENU;
    }
	if (released && _cursIdx == 2) {
		std::shared_ptr<IMenu> tmp = getptr();
		std::unique_ptr<Indie::Settings> settings = std::make_unique<Indie::Settings>(tmp);
		settings->run();
	}
	if (released && _cursIdx == 3)
		return LAST_MENU;
	if (key == Input::Button::UP || key == Input::Button::DOWN)
		_menuActions[0]->play();
	if (key == Input::Button::UP) {
		if (_cursIdx == 0)
			_cursIdx = _buttons.size() - 1;
		else
			_cursIdx -= 1;
	}
	if (key == Input::Button::DOWN) {
		if (_cursIdx == _buttons.size() - 1)
			_cursIdx = 0;
		else
			_cursIdx += 1;
	}
	return NOTHING;
}

void MainMenu::drawUi()
{
	int i = 1;
	int screenHeight = _raylib->getScreenHeight();
	int screenWidth = _raylib->getScreenWidth();
	int x = 0;
	int y = 0;

	_menuMusic[0]->update();
    _raylib->drawRectangle(0, 0, screenWidth, screenHeight, Indie::CppColor(WHITE));
	for (auto &but : _buttons) {
		x = screenWidth / 2 - but->getWidth() / 2;
		y = screenHeight / 6 * i;
		but->reposition(x, y);
		but->resize(screenWidth, screenHeight);
		_raylib->drawButton(but);
		i++;
	}
}

std::vector<std::shared_ptr<Indie::IAudio>> MainMenu::getSound() const
{
	return _menuActions;
}

std::vector<std::shared_ptr<Indie::IAudio>> MainMenu::getMusic() const
{
	return _menuMusic;
}