/*
** EPITECH PROJECT, 2022
** B-YEP-400-PAR-4-1-indiestudio-tom.fuller
** File description:
** Color
*/

#include "Color.hpp"

Indie::CppColor::CppColor(const Color &color)
{
	_color = color;
}

Color Indie::CppColor::getColor() const
{
	return _color;
}

void Indie::CppColor::setColor(const CppColor &color)
{
	_color = color.getColor();
}
