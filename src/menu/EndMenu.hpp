/*
** EPITECH PROJECT, 2022
** B-YEP-400-PAR-4-1-indiestudio-tom.fuller
** File description:
** EndMenu
*/

#ifndef ENDMENU_HPP_
	#define ENDMENU_HPP_

	#include "IMenu.hpp"
	#include "Raylib.hpp"

	#define END_FONT_SIZE 60

namespace Menu {
	class EndMenu : public IMenu {
		public:
			EndMenu(const std::shared_ptr<IMenu> &menu, const bool &win, const std::string &playerName = "");
			~EndMenu() override = default;
			void startMenu() override;
			void update() override;
			Return_Status event() override;
			bool closeMenu() const override;
			int run() override;
			void drawUi() override;
			std::vector<std::shared_ptr<Indie::IAudio>> getSound() const override;
			std::vector<std::shared_ptr<Indie::IAudio>> getMusic() const override;
		private:
			std::unique_ptr<Raylib> _raylib;
			bool _win;
			std::shared_ptr<IMenu> _menu;
			std::string _name;
	};
}

#endif
