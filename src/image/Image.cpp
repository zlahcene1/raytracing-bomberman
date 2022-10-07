/*
** EPITECH PROJECT, 2022
** indie
** File description:
** Image
*/

#include "Image.hpp"
#include "IMenu.hpp"

Indie::CppImage::CppImage(const std::string &filePath)
{
	_tex = LoadTexture(filePath.c_str());
    _rec = CppRectangle(0, 0, _tex.width, _tex.height);
	_pos = CppVector2(0.0, 0.0);
	_initSize = CppVector2(_tex.width, _tex.height);
}

Indie::CppImage::~CppImage()
{
    UnloadTexture(_tex);
}

const Texture2D &Indie::CppImage::getTexture()
{
	return _tex;
}

Indie::CppRectangle Indie::CppImage::getRectangle() const
{
    return _rec;
}

Indie::CppVector2 Indie::CppImage::getRecSize() const
{
	return _rec.getRecSize();
}

Indie::CppVector2 Indie::CppImage::getPos() const
{
	return _pos;
}

void Indie::CppImage::setPos(const int &posX, const int &posY)
{
	_pos.setVector2(static_cast<float>(posX), static_cast<float>(posY));
}

void Indie::CppImage::setRecSize(const int &screenWidth, const int &screenHeight)
{
	int width = _initSize.getVectorX() * screenWidth / WIDTH;
	int height = _initSize.getVectorY() * screenHeight / HEIGHT;

	_rec.setRectangleSize(width, height);
}

Indie::CppRectangle Indie::CppImage::getRectangleBounds() const
{
	CppVector2 size = _rec.getRecSize();

	return CppRectangle(_pos.getVectorX(), _pos.getVectorY(), size.getVectorX(), size.getVectorY());
}