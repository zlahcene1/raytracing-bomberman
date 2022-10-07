/*
** EPITECH PROJECT, 2022
** B-YEP-400-PAR-4-1-indiestudio-tom.fuller
** File description:
** Input
*/

#include "Input.hpp"

Gui::InputBox::InputBox(const int &size, const std::string &placeHolder)
: _input(placeHolder), _maxSize(size), _state(NOT_SELECTED)
{
	setState(NOT_SELECTED);
}

void Gui::InputBox::addCharacter(const Input::Button &key)
{
	int len = _input.size();

	if (len < _maxSize) {
		if (len - 1 < 0)
			len = 0;
		_input.insert(_input.begin() + len - 1, static_cast<char>(key));
	}
}

void Gui::InputBox::removeCharacter()
{
	int len = _input.size();

	if (len > 1)
		_input.erase(_input.end() - 2);
}

void Gui::InputBox::setTextColor(const Indie::CppColor &color)
{
	_textColor = color;
}

void Gui::InputBox::setForeGround(const Indie::CppColor &color)
{
	_foreGround = color;
}

void Gui::InputBox::setBackground(const Indie::CppColor &color)
{
	_backGround = color;
}

void Gui::InputBox::setState(const ButtonState &state)
{
	_state = state;
	if (_state == SELECTED) {
		_backGround.setColor(RED);
		_foreGround.setColor(BLACK);
		_textColor.setColor(RED);
		if (_input.size() < static_cast<long unsigned int>(_maxSize) && _input.back() != '_')
			_input.insert(_input.end(), '_');
	} else {
		_backGround.setColor(WHITE);
		_foreGround.setColor(BLACK);
		_textColor.setColor(WHITE);
		if (_input.size() >= 1 && _input.back() == '_')
			_input.erase(_input.end() - 1);
	}
}

Gui::ButtonState Gui::InputBox::getState() const
{
	return _state;
}

std::string Gui::InputBox::getText() const
{
	return _input;
}

Indie::CppRectangle Gui::InputBox::getBounds() const
{
	return _bounds;
}

void Gui::InputBox::setPos(const float &posX, const float &posY)
{
	_bounds.setRectanglePos(posX, posY);
}

void Gui::InputBox::setSize(const float &width, const float &height)
{
	_bounds.setRectangleSize(width, height);
}

Indie::CppColor Gui::InputBox::getBackgroundColor() const
{
	return _backGround;
}

Indie::CppColor Gui::InputBox::getForeGroundColor() const
{
	return _foreGround;
}

Indie::CppColor Gui::InputBox::getTextColor() const
{
	return _textColor;
}