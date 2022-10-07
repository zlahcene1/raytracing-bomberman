/*
** EPITECH PROJECT, 2022
** B-YEP-400-PAR-4-1-indiestudio-tom.fuller
** File description:
** EndMenu
*/

#include "EndMenu.hpp"
#include "MainMenu.hpp"

Menu::EndMenu::EndMenu(const std::shared_ptr<IMenu> &menu, const bool &win, const std::string &playerName)
: _raylib(std::make_unique<Raylib>()), _win(win), _menu(menu), _name(playerName)
{}

bool Menu::EndMenu::closeMenu() const
{
	return _raylib->windowShouldClose();
}

int Menu::EndMenu::run()
{
	while (!closeMenu()) {
		update();
		if (event())
			break;
	}
	return 0;
}

void Menu::EndMenu::startMenu()
{}

void Menu::EndMenu::update()
{
	int screenWidth = _raylib->getScreenWidth();
	int screenHeight = _raylib->getScreenHeight();
	int font_size = END_FONT_SIZE * (screenWidth * screenHeight) / (WIDTH * HEIGHT);
	std::string header;
	int textSize = 0;
	Indie::CppColor color;
	int textSize2 = 0;
	int textSize3 = 0;

	if (_win) {
		color = YELLOW;
		header = "Player: " + _name + " won !!!";
	} else {
		color = RED;
		header = "You Lost D:";
	}
	textSize = _raylib->measureText(header, font_size);
	_raylib->beginDrawing();
	_menu->drawUi();
	_raylib->drawRectangle(0, 0, screenWidth, screenHeight, Color({0, 0, 0, 220}));
	_raylib->drawText(header, screenWidth / 2 - textSize / 2, screenHeight / 2 * 0.90, font_size, color);
	header = "Press any key to exit";
	if (_win) {
		textSize2 = _raylib->measureText(_name, font_size);
		textSize3 = _raylib->measureText("Player: ", font_size);
		_raylib->drawRectangle(screenWidth / 2 - textSize / 2 + textSize3, screenHeight / 2 * 0.90 * 1.11, textSize2 * 1.09, 2, color);
	}
	font_size *= 0.30;
	textSize = _raylib->measureText(header, font_size);
	_raylib->drawText(header, screenWidth / 2 - textSize / 2, screenHeight / 2 * 1.10, font_size, color);
	_raylib->endDrawing();
}

Return_Status Menu::EndMenu::event()
{
	if (_raylib->isKeyPressed() != Input::Button::NONE)
		return LAST_MENU;
	return NOTHING;
}

void Menu::EndMenu::drawUi()
{}

std::vector<std::shared_ptr<Indie::IAudio>> Menu::EndMenu::getSound() const
{
	return {};
}

std::vector<std::shared_ptr<Indie::IAudio>> Menu::EndMenu::getMusic() const
{
	return {};
}