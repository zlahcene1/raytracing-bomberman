/*
** EPITECH PROJECT, 2022
** B-YEP-400-PAR-4-1-indiestudio-tom.fuller
** File description:
** Button
*/

#ifndef BUTTON_HPP_
	#define BUTTON_HPP_

	#include "raylib.h"
	#include <string>
	#include "Color.hpp"
	#include <memory>

namespace Gui {
	enum ButtonState {
		NOT_SELECTED,
		SELECTED,
		PRESSED,
		DISABLED
	};

	class Button {
		public:
			Button();
			Button(const int &posX, const int &posY, const float &, const float &,
			const Indie::CppColor &, const Indie::CppColor &,
			const std::string &, const Indie::CppColor &);
			Button(Button &) = delete;
			Button &operator=(const Button &) = delete;
			~Button();
			void resize(const int &newWidth, const int &newHeight);
			void reposition(const int &newX, const int &newY);
			int getPosX() const;
			int getPosY() const;
			int getWidth() const;
			int getHeight() const;
			int getFontSize() const;
			std::string getText() const;
			Indie::CppColor getForeGround() const;
			Indie::CppColor getBackGround() const;
			Indie::CppColor getTextColor() const;
			void setForeGround(const Indie::CppColor &);
			void setBackground(const Indie::CppColor &);
			void setTextColor(const Indie::CppColor &);
			void setState(const ButtonState &);
			ButtonState getState() const;
		private:
			int _posX;
			int _posY;
			int _width;
			int _height;
			Indie::CppColor _foreGround;
			Indie::CppColor _backGround;
			std::string _text;
			Indie::CppColor _textColor;
			int _fontSize;
			float _wcoef;
			float _hcoef;
			ButtonState _state;
	};
	void update_buttons(std::vector<std::unique_ptr<Gui::Button>> &buttons, const int &idx);
}

#endif /* !BUTTON_HPP_ */
