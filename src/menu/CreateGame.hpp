/*
** EPITECH PROJECT, 2022
** B-YEP-400-PAR-4-1-indiestudio-tom.fuller
** File description:
** CreateGame
*/

#ifndef CREATEGAME_HPP_
	#define CREATEGAME_HPP_

	#include "IMenu.hpp"
	#include "Input.hpp"
	#include "Raylib.hpp"

	#define ACT_BUTTON_WIDTH 300
	#define ACT_BUTTON_HEIGHT 100
	#define ACT_FONT_SIZE 30
	#define PL_BUTTON_WIDTH 1000
	#define PL_BUTTON_HEIGHT 100
	#define MAX_PLAYERS 4

namespace Menu {
	class CreateGame : public IMenu {
		public:
			CreateGame(std::vector<std::shared_ptr<Indie::IAudio>> &menuMusic,
			std::vector<std::shared_ptr<Indie::IAudio>> &menuAudio);
			~CreateGame() override = default;
			void startMenu() override;
        	void update() override;
        	Return_Status event() override;
        	bool closeMenu() const override;
			int run() override;
        	void drawUi() override;
			std::vector<std::shared_ptr<Indie::IAudio>> getSound() const override;
			std::vector<std::shared_ptr<Indie::IAudio>> getMusic() const override;
			bool checkSelected(const Indie::CppVector2 &mousePos, std::unique_ptr<Gui::Button> &button);
			void insertInputBox(const bool &type);
			void popInputBox(const bool &type);
			void launchGame();
		private:
			std::vector<std::shared_ptr<Indie::IAudio>> _music;
			std::vector<std::shared_ptr<Indie::IAudio>> _audio;
			std::vector<std::unique_ptr<Gui::InputBox>> _inputs;
			std::vector<bool> _inputTypes;
			std::unique_ptr<Gui::Button> _addPlayer;
			std::unique_ptr<Gui::Button> _removePlayer;
			std::unique_ptr<Gui::Button> _addBot;
			std::unique_ptr<Gui::Button> _removeBot;
			std::unique_ptr<Gui::Button> _play;
			std::unique_ptr<Raylib> _raylib;
			int _playerId;
			int _botId;
	};
}

#endif /* !CREATEGAME_HPP_ */
