/*
** EPITECH PROJECT, 2022
** B-YEP-400-PAR-4-1-indiestudio-tom.fuller
** File description:
** Cursor
*/

#ifndef CURSOR_HPP_
	#define CURSOR_HPP_

	#include "Image.hpp"
	#include "Vector2.hpp"
	#include <string>
	#include <memory>
	#include <iostream>
	#include <iomanip>
	#include <cmath>

namespace Gui {
	template <class AudioType>
	class SoundBar {
		public:
			SoundBar() = default;

			~SoundBar() = default;

			SoundBar(const std::string &cursorPath, const std::string &barPath, const float &volume, std::vector<std::shared_ptr<AudioType>> audio)
			: _volume(volume), _audio(audio)
			{
				_cursor = *new Indie::CppImage(cursorPath);
				_bar = *new Indie::CppImage(barPath);
			}
			void setCursorPos(const float &posX)
			{
				Indie::CppVector2 posCursor = _cursor.getPos();
				Indie::CppVector2 sizeCursor = _cursor.getRecSize();
				Indie::CppVector2 posBar = _bar.getPos();
				Indie::CppVector2 sizeBar = _bar.getRecSize();
				int newX = posBar.getVectorX() + (posX * sizeBar.getVectorX()) - sizeCursor.getVectorX() / 2.0;
				int newY = sizeBar.getVectorY() / 2.0 - sizeCursor.getVectorY() / 2 + posBar.getVectorY();

				if (newX < posBar.getVectorX())
					newX = posBar.getVectorX();
				if (newX + sizeCursor.getVectorX() >= posBar.getVectorX() + sizeBar.getVectorX())
					newX = posBar.getVectorX() + sizeBar.getVectorX() - sizeCursor.getVectorX();
				_cursor.setPos(newX, newY);
			}

			void setBarPos(const int &posX, const int &posY)
			{
				_bar.setPos(posX, posY);
			}

			void setPos(const int &posX, const int &posY)
			{
				setBarPos(posX, posY);
				setCursorPos(_volume);
			}

			Indie::CppVector2 getBarPos() const
			{
				return _bar.getPos();
			}

			float getVolume() const
			{
				return _volume;
			}

			Indie::CppImage &getBar()
			{
				return _bar;
			}

			Indie::CppImage &getCursor()
			{
				return _cursor;
			}

			void setSize(const int &width, const int &height)
			{
				_cursor.setRecSize(width, height);
				_bar.setRecSize(width, height);
			}

			void setVolume(const float &posX)
			{
				Indie::CppVector2 sizeBar = _bar.getRecSize();
				Indie::CppVector2 posBar = _bar.getPos();

				_volume = (posX - posBar.getVectorX()) / sizeBar.getVectorX();
				std::cout << _volume << std::endl;
				_volume = std::floor(_volume * 100) / 100.0;
				if (_volume < 0)
					_volume = 0;
				if (_volume > 1.0)
					_volume = 1.0;
				setCursorPos(_volume);
				for (auto &audio : _audio)
					audio->setVolume(_volume);
			}

		private:
			Indie::CppImage _cursor;
			Indie::CppImage _bar;
			float _volume;
			std::vector<std::shared_ptr<AudioType>> _audio;
	};
}

#endif
