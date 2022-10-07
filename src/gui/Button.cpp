/*
** EPITECH PROJECT, 2022
** B-YEP-400-PAR-4-1-indiestudio-tom.fuller
** File description:
** Button
*/

#include "IMenu.hpp"
#include "Button.hpp"

void Gui::update_buttons(std::vector<std::unique_ptr<Gui::Button>> &buttons, const int &idx)
{
	for (auto &button : buttons) {
		if (buttons[idx]->getState() != Gui::ButtonState::PRESSED && button->getState() != Gui::ButtonState::DISABLED)
			button->setState(Gui::NOT_SELECTED);
	}
	if (buttons[idx]->getState() != Gui::ButtonState::PRESSED && buttons[idx]->getState() != Gui::ButtonState::DISABLED)
		buttons[idx]->setState(Gui::SELECTED);
}

Gui::Button::Button()
{}

Gui::Button::Button(const int &posX, const int &posY, const float &wcoef,
	const float &hcoef, const Indie::CppColor &foreGround, const Indie::CppColor &backGround,
	const std::string &text, const Indie::CppColor &textColor)
: _posX(posX), _posY(posY), _width(0), _height(0),
  _foreGround(foreGround), _backGround(backGround), _text(text),
  _textColor(textColor), _fontSize(DEFAULT_FONT_SIZE * _width / BUTTON_WIDTH),
  _wcoef(wcoef), _hcoef(hcoef), _state(NOT_SELECTED)
{}

int Gui::Button::getFontSize() const
{
	return _fontSize;
}

void Gui::Button::setTextColor(const Indie::CppColor &color)
{
	_textColor = color;
}

void Gui::Button::setForeGround(const Indie::CppColor &color)
{
	_foreGround = color;
}

void Gui::Button::setBackground(const Indie::CppColor &color)
{
	_backGround = color;
}

void Gui::Button::reposition(const int &newX, const int &newY)
{
	_posX = newX;
	_posY =  newY;
}

void Gui::Button::resize(const int &screenWidth, const int &screenHeight)
{
	float nb1;

	_width = static_cast<int>(static_cast<float>(screenWidth) * _wcoef);
	_height = static_cast<int>(static_cast<float>(screenHeight) * _hcoef);
	nb1 = screenWidth * screenHeight;
	_fontSize = nb1 / 100000 * 1.80;
}

int Gui::Button::getPosX() const
{
	return _posX;
}

int Gui::Button::getPosY() const
{
	return _posY;
}

int Gui::Button::getWidth() const
{
	return _width;
}

int Gui::Button::getHeight() const
{
	return _height;
}

Indie::CppColor Gui::Button::getForeGround() const
{
	return _foreGround;
}

Indie::CppColor Gui::Button::getBackGround() const
{
	return _backGround;
}

std::string Gui::Button::getText() const
{
	return _text;
}

Indie::CppColor Gui::Button::getTextColor() const
{
	return _textColor;
}

void Gui::Button::setState(const ButtonState &state)
{
	_state = state;
	if (state == NOT_SELECTED) {
		setBackground(RED);
		setForeGround(BLACK);
		setTextColor(WHITE);
	} else if (state == SELECTED) {
		setBackground(RED);
		setForeGround(WHITE);
		setTextColor(BLACK);
	} else if (state == PRESSED){
		setTextColor(YELLOW);
	} else {
		setBackground(Color({35, 34, 36, 255}));
		setForeGround(Color({47, 46, 48, 255}));
		setTextColor(BLACK);
	}
}

Gui::Button::~Button()
{
	std::cout << "Delete Button" << " " << getText() << std::endl;
}

Gui::ButtonState Gui::Button::getState() const
{
	return _state;
}