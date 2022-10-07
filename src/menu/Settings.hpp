/*
** EPITECH PROJECT, 2022
** B-YEP-400-PAR-4-1-indiestudio-tom.fuller
** File description:
** Settings
*/

#ifndef SETTINGS_HPP_
	#define SETTINGS_HPP_

	#include "IMenu.hpp"
	#include "Raylib.hpp"
	#include "DropDown.hpp"
	#include "Sound.hpp"
	#include "Music.hpp"
	#include "SoundBar.hpp"

	#define S_DD_WIDTH 300
	#define S_DD_HEIGHT 50
	#define FL_SCREEN_WHIDTH 300
	#define FL_SCREEN_HEIGHT 100
	#define FONT_SIZE 22
	#define GRAPHICS_HEADER "Graphics"
	#define AUDIO_SETTINGS "Audio"

namespace Indie {
	class Settings : public IMenu {
		public:
			Settings() = default;
			Settings(const std::shared_ptr<IMenu> &menu);
			~Settings() override;
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
			std::shared_ptr<IMenu> _menu;
			std::unique_ptr<Indie::CppSound> _menuActions;
			std::unique_ptr<Gui::DropDown> _resolutionDropDown;
			std::unique_ptr<Gui::SoundBar<Indie::IAudio>> _music;
			std::unique_ptr<Gui::SoundBar<Indie::IAudio>> _sound;
			std::unique_ptr<Gui::Button> _fullScreen;
	};
}

#endif /* !SETTINGS_HPP_ */