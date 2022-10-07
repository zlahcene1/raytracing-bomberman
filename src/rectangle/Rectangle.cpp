/*
** EPITECH PROJECT, 2022
** B-YEP-400-PAR-4-1-indiestudio-tom.fuller
** File description:
** Rectangle
*/

#include "Rectangle.hpp"

Indie::CppRectangle::CppRectangle(const float &x, const float &y,
const float &width, const float &height)
{
	_rectangle.x = x;
	_rectangle.y = y;
	_rectangle.width = width;
	_rectangle.height = height;
}

void Indie::CppRectangle::setRectanglePos(const float &posX, const float &posY)
{
	_rectangle.x = posX;
	_rectangle.y = posY;
}

void Indie::CppRectangle::setRectangleSize(const float &width, const float &height)
{
	_rectangle.width = width;
	_rectangle.height = height;
}

Rectangle Indie::CppRectangle::getRectangle() const
{
	return _rectangle;
}

Indie::CppVector2 Indie::CppRectangle::getRecSize() const
{
	return CppVector2(_rectangle.width, _rectangle.height);
}