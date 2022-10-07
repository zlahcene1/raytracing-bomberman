/*
** EPITECH PROJECT, 2022
** B-YEP-400-PAR-4-1-indiestudio-tom.fuller
** File description:
** Vector2
*/

#include "Vector2.hpp"

Indie::CppVector2::CppVector2(const float &x, const float &y)
{
	_vector.x = x;
	_vector.y = y;
}

Vector2 Indie::CppVector2::getVector2() const
{
	return _vector;
}

void Indie::CppVector2::setVector2(const float &x, const float &y)
{
	_vector.x = x;
	_vector.y = y;
}

float Indie::CppVector2::getVectorX() const
{
	return _vector.x;
}

float Indie::CppVector2::getVectorY() const
{
	return _vector.y;
}