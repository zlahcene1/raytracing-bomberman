/*
** EPITECH PROJECT, 2022
** B-YEP-400-PAR-4-1-indiestudio-tom.fuller
** File description:
** DropDown
*/

#ifndef DROPDOWN_HPP_
	#define DROPDOWN_HPP_

	#include <vector>
	#include "Button.hpp"
	#include "Vector2.hpp"
	#include <memory>

namespace Gui {
	struct DropDown {
		public:
			DropDown() = default;
			DropDown(std::vector<std::unique_ptr<Gui::Button>> &content,
			const int &posX = 0, const int &posY = 0);
			~DropDown() = default;
			DropDown(DropDown &) = delete;
			DropDown &operator=(const DropDown &) = delete;
			std::vector<std::unique_ptr<Gui::Button>> &getButtons();
			void reposition(const int &posX, const int &posY);
			void resize(const int &screenWidth, const int &screenHeight);
			int getFontSize() const;
			bool getSelected() const;
			void setSelected(const bool &);
			std::unique_ptr<Gui::Button> &getHeader();
			std::unique_ptr<Gui::Button> &selectButton(const Indie::CppVector2 &);
			void refreshButtonsState();
			bool isMouseOnButton(const Indie::CppVector2 &);
		private:
			std::vector<std::unique_ptr<Gui::Button>> _content;
			int _posX;
			int _posY;
			int _fontSize;
			bool _selected;
	};
}

#endif
