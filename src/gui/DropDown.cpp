/*
** EPITECH PROJECT, 2022
** B-YEP-400-PAR-4-1-indiestudio-tom.fuller
** File description:
** DropDown
*/

#include "DropDown.hpp"
#include "IMenu.hpp"
#include "Errors.hpp"

Gui::DropDown::DropDown(std::vector<std::unique_ptr<Gui::Button>> &content,
const int &posX, const int &posY)
: _content(std::move(content)), _posX(posX), _posY(posY), _selected(false)
{
	reposition(_posX, _posY);
}

int Gui::DropDown::getFontSize() const
{
	return _fontSize;
}

std::unique_ptr<Gui::Button> &Gui::DropDown::getHeader()
{
	return _content[0];
}

std::vector<std::unique_ptr<Gui::Button>> &Gui::DropDown::getButtons()
{
	return _content;
}

bool Gui::DropDown::getSelected() const
{
	return _selected;
}

void Gui::DropDown::setSelected(const bool &status)
{
	_selected = status;
	if (!_selected)
		for (auto &button : _content)
			button->reposition(_content[0]->getPosX(), _content[0]->getPosY());
	else
		reposition(_posX, _posY);

}

void Gui::DropDown::reposition(const int &posX, const int &posY)
{
	int y = posY;

	for (auto &button : _content) {
		button->reposition(posX, y);
		y += button->getHeight() + 10;
	}
}

void Gui::DropDown::resize(const int &screenWidth, const int &screenheight)
{
	for (auto &button : _content)
		button->resize(screenWidth, screenheight);
	reposition(_posX, _posY);
}

void Gui::DropDown::refreshButtonsState()
{
	for (auto &button : _content) {
		button->setState(NOT_SELECTED);
	}
}

bool Gui::DropDown::isMouseOnButton(const Indie::CppVector2 &mousePos)
{
	float posX = mousePos.getVectorX();
	float posY = mousePos.getVectorY();

	for (auto &button : _content) {
		if ((posX > button->getPosX() && posX <= button->getWidth() + button->getPosX())
		&& (posY > button->getPosY() && posY < button->getHeight() + button->getPosY()))
			return true;
	}
	return false;
}

std::unique_ptr<Gui::Button> &Gui::DropDown::selectButton(const Indie::CppVector2 &mousePos)
{
	float posX = mousePos.getVectorX();
	float posY = mousePos.getVectorY();

	for (auto &button : _content) {
		if ((posX > button->getPosX() && posX <= button->getWidth() + button->getPosX())
		&& (posY > button->getPosY() && posY < button->getHeight() + button->getPosY()))
			return button;
	}
	throw Error::DropDownErrorSelectedButtonNotFound("selectButton()", "was about to return an empty ref");
}