/*
** EPITECH PROJECT, 2022
** bomberman
** File description:
** Pause
*/

#ifndef PAUSE_HPP_
    #define PAUSE_HPP_

    #include "Utils.hpp"
    #include "IMenu.hpp"
	#include "Button.hpp"
	#include "IAudio.hpp"

	#define PS_BUTTON_WIDTH 400
	#define PS_BUTTON_HEIGHT 100

namespace Menu {
	class Pause : public IMenu {
		public:
			Pause(const std::shared_ptr<IMenu> &menu,
			const std::vector<std::shared_ptr<Indie::IAudio>> &music,
 			const std::vector<std::shared_ptr<Indie::IAudio>> &audio);
			~Pause() override = default;
			void startMenu() override;
			void update() override;
			Return_Status event() override;
			bool closeMenu() const override;
			int run() override;
			void drawUi() override;
			std::vector<std::shared_ptr<Indie::IAudio>> getSound() const override;
			std::vector<std::shared_ptr<Indie::IAudio>> getMusic() const override;
		private:
			std::vector<std::unique_ptr<Gui::Button>> _buttons;
			std::shared_ptr<IMenu> _menu;
			std::unique_ptr<Raylib> _raylib;
			std::vector<std::shared_ptr<Indie::IAudio>> _music;
 			std::vector<std::shared_ptr<Indie::IAudio>> _audio;
			std::size_t _idx;
	};
}

#endif /* !PAUSE_HPP_ */