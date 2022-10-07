/*
** EPITECH PROJECT, 2022
** bomberman
** File description:
** Pause
*/

#include "Pause.hpp"
#include "Settings.hpp"

Menu::Pause::Pause(const std::shared_ptr<IMenu> &menu,
 const std::vector<std::shared_ptr<Indie::IAudio>> &music,
 const std::vector<std::shared_ptr<Indie::IAudio>> &audio)
: _menu(menu), _raylib(std::make_unique<Raylib>()), _music(music), _audio(audio), _idx(0)
{
	float widthCoef = static_cast<float>(PS_BUTTON_WIDTH) / static_cast<float>(WIDTH);
	float heightCoef = static_cast<float>(PS_BUTTON_HEIGHT) / static_cast<float>(HEIGHT);

	_buttons.push_back(std::make_unique<Gui::Button>(0, 0, widthCoef, heightCoef, BLACK, RED, "Resume", WHITE));
	_buttons.push_back(std::make_unique<Gui::Button>(0, 0, widthCoef, heightCoef, BLACK, RED, "Settings", WHITE));
	_buttons.push_back(std::make_unique<Gui::Button>(0, 0, widthCoef, heightCoef, BLACK, RED, "Save and Exit", WHITE));
}

void Menu::Pause::drawUi()
{}

bool Menu::Pause::closeMenu() const
{
	return _raylib->windowShouldClose();
}

int Menu::Pause::run()
{
	Return_Status status = NOTHING;

	_raylib->hideCursor();
	while (!closeMenu()) {
		update();
		status = event();
		if (status == EXIT)
			return 1;
		if (status == LAST_MENU)
			return 0;
	}
	return 0;
}

void Menu::Pause::startMenu()
{}

void Menu::Pause::update()
{
	int screenWidth = _raylib->getScreenWidth();
	int screenHeight = _raylib->getScreenHeight();
	int it = 1;

	_raylib->beginDrawing();
	_menu->drawUi();
	_raylib->drawRectangle(0, 0, screenWidth, screenHeight, Color({0, 0, 0, 220}));
	for (auto &button : _buttons) {
		button->reposition(screenWidth / 2 - button->getWidth() / 2, screenHeight * it / 5);
		button->resize(screenWidth, screenHeight);
		_raylib->drawButton(button);
		it += 1;
	}
	_music[0]->update();
	_raylib->endDrawing();
}

Return_Status Menu::Pause::event()
{
	Input::Button button = _raylib->isKeyPressed();
	bool isReleased = _raylib->isKeyReleased(Input::Button::ENTER);

	Gui::update_buttons(_buttons, _idx);
	if (button == Input::Button::DOWN) {
		_audio[0]->play();
		if (_idx == _buttons.size() - 1)
			_idx = 0;
		else
			_idx += 1;
	}
	if (button == Input::Button::UP) {
		_audio[0]->play();
		if (_idx == 0)
			_idx = _buttons.size() - 1;
		else
			_idx -= 1;
	}
	if (button == Input::Button::ENTER)
		_buttons[_idx]->setState(Gui::PRESSED);
	if (isReleased)
		_buttons[_idx]->setState(Gui::SELECTED);
	if (isReleased && _idx == 0)
		return LAST_MENU;
	if (isReleased && _idx == 1) {
		std::unique_ptr<IMenu> settings = std::make_unique<Indie::Settings>(_menu);
		settings->run();
	}
	if (isReleased && _idx == 2)
		return EXIT;
	return NOTHING;
}

std::vector<std::shared_ptr<Indie::IAudio>> Menu::Pause::getSound() const
{
	return _music;
}

std::vector<std::shared_ptr<Indie::IAudio>> Menu::Pause::getMusic() const
{
	return _audio;
}