/*
** EPITECH PROJECT, 2022
** B-YEP-400-PAR-4-1-indiestudio-tom.fuller
** File description:
** Input
*/

#ifndef INPUT_HPP_
	#define INPUT_HPP_

	#include <string>
	#include "Utils.hpp"
	#include "Button.hpp"
	#include "Color.hpp"
	#include "Rectangle.hpp"

	#define INPUT_FONT_SIZE 25
	#define INPUT_WIDTH 200
	#define INPUT_HEIGHT 50

namespace Gui {
	class InputBox {
		public:
			InputBox(const int &maxSize, const std::string &placeHolder = "");
			~InputBox() = default;
			void addCharacter(const Input::Button &key);
			void removeCharacter();
			void setState(const ButtonState &);
			ButtonState getState() const;
			std::string getText() const;
			Indie::CppRectangle getBounds() const;
			void setPos(const float &posX, const float &posY);
			void setSize(const float &width, const float &height);
			Indie::CppColor getBackgroundColor() const;
			Indie::CppColor getForeGroundColor() const;
			Indie::CppColor getTextColor() const;
			void setForeGround(const Indie::CppColor &);
			void setBackground(const Indie::CppColor &);
			void setTextColor(const Indie::CppColor &);
		private:
			Indie::CppRectangle _bounds;
			std::string _input;
			int _maxSize;
			ButtonState _state;
			Indie::CppColor _backGround;
			Indie::CppColor _foreGround;
			Indie::CppColor _textColor;
	};
}

#endif /* !INPUT_HPP_ */
